#![no_std]
#![no_main]

use embassy_executor::Spawner;
use embassy_net::{dns::DnsQueryType, tcp::TcpSocket, Stack, StackResources};
use embassy_time::{Duration, Timer};
use embedded_tls::{Aes128GcmSha256, NoVerify, TlsConfig, TlsConnection, TlsContext};
use esp_alloc as _;
use esp_backtrace as _;
use esp_hal::{
    peripheral::Peripheral,
    prelude::*,
    rng::{Rng, Trng},
    timer::timg::TimerGroup,
};
use esp_println::println;
use esp_wifi::{
    wifi::{
        AuthMethod, ClientConfiguration, Configuration, WifiController, WifiDevice, WifiEvent,
        WifiStaDevice, WifiState,
    },
    EspWifiInitFor, EspWifiInitialization,
};
use rust_mqtt::{
    client::{client::MqttClient, client_config::ClientConfig},
    utils::rng_generator::CountingRng,
};

// When you are okay with using a nightly compiler it's better to use https://docs.rs/static_cell/2.1.0/static_cell/macro.make_static.html
macro_rules! mk_static {
    ($t:ty,$val:expr) => {{
        static STATIC_CELL: static_cell::StaticCell<$t> = static_cell::StaticCell::new();
        #[deny(unused_attributes)]
        let x = STATIC_CELL.uninit().write(($val));
        x
    }};
}

const SSID: &str = env!("SSID");
const PASSWORD: &str = env!("PASSWORD");

#[esp_hal_embassy::main]
async fn main(spawner: Spawner) -> ! {
    // Unwrap peripherals
    esp_println::logger::init_logger_from_env();
    let mut peripherals = esp_hal::init({
        let mut config = esp_hal::Config::default();
        config.cpu_clock = CpuClock::max();
        config
    });

    // DO NOT MOVE
    esp_alloc::heap_allocator!(72 * 1024);

    // Config timers for WiFi connection
    let timg0 = TimerGroup::new(peripherals.TIMG0);
    let init: EspWifiInitialization;
    unsafe {
        init = esp_wifi::init(
            EspWifiInitFor::Wifi,
            timg0.timer0,
            Rng::new(peripherals.RNG.clone_unchecked()),
            peripherals.RADIO_CLK,
        )
        .unwrap();
    }

    // Config WiFi interface
    let wifi = peripherals.WIFI;
    let (wifi_interface, controller) =
        esp_wifi::wifi::new_with_mode(&init, wifi, WifiStaDevice).unwrap();
    let timg1 = TimerGroup::new(peripherals.TIMG1);
    esp_hal_embassy::init(timg1.timer0);
    let config = embassy_net::Config::dhcpv4(Default::default());

    // Config WiFi device
    let seed = 1234; // very random, very secure seed
    let stack = &*mk_static!(
        Stack<WifiDevice<'_, WifiStaDevice>>,
        Stack::new(
            wifi_interface,
            config,
            mk_static!(StackResources<3>, StackResources::<3>::new()),
            seed
        )
    );

    // Config TLS
    let mut read_record_buffer = [0; 16384];
    let mut write_record_buffer = [0; 16384];
    let tls_config: embedded_tls::TlsConfig<'_, Aes128GcmSha256> = TlsConfig::new()
        .with_server_name("mqtt.eclipseprojects.io")
        .enable_rsa_signatures();
    let mut tls_rng = Trng::new(peripherals.RNG, peripherals.ADC1);

    // Start network
    spawner.spawn(connection(controller)).ok();
    spawner.spawn(net_task(stack)).ok();

    loop {
        if stack.is_link_up() {
            break;
        }
        Timer::after(Duration::from_millis(500)).await;
    }

    println!("Waiting to get IP address...");
    loop {
        if let Some(config) = stack.config_v4() {
            println!("Got IP: {}", config.address);
            break;
        }
        Timer::after(Duration::from_millis(500)).await;
    }

    loop {
        Timer::after(Duration::from_millis(1_000)).await;

        // Create TCP Socket
        let mut tcp_rx_buffer = [0; 4096];
        let mut tcp_tx_buffer = [0; 4096];
        let mut socket = TcpSocket::new(stack, &mut tcp_rx_buffer, &mut tcp_tx_buffer);
        socket.set_timeout(Some(embassy_time::Duration::from_secs(10)));

        println!("Connecting to broker...");
        let address = match stack
            .dns_query("mqtt.eclipseprojects.io", DnsQueryType::A)
            .await
            .map(|a| a[0])
        {
            Ok(address) => address,
            Err(e) => {
                println!("DNS lookup error: {e:?}");
                continue;
            }
        };
        let remote_endpoint = (address, 8883);
        let r = socket.connect(remote_endpoint).await;
        if let Err(e) = r {
            println!("connect error: {:?}", e);
            continue;
        }
        println!("a");

        // Open TLS connection
        let mut tls = TlsConnection::new(socket, &mut read_record_buffer, &mut write_record_buffer);
        tls.open::<Trng, NoVerify>(TlsContext::new(&tls_config, &mut tls_rng))
            .await
            .expect("error establishing TLS connection");
        println!("b");

        // Config MQTT
        let mut mqtt_config = ClientConfig::new(
            rust_mqtt::client::client_config::MqttVersion::MQTTv5,
            CountingRng(20000),
        );
        mqtt_config
            .add_max_subscribe_qos(rust_mqtt::packet::v5::publish_packet::QualityOfService::QoS1);
        mqtt_config.add_client_id("e91ed534423ce0fc8a7f16f4ac7f8f2d");
        mqtt_config.max_packet_size = 100;
        // mqtt_config.add_username("user");
        // mqtt_config.add_password("pass");
        let mut recv_buffer = [0; 80];
        let mut write_buffer = [0; 80];
        println!("c");

        // Open MQTT Connection
        let mut client = MqttClient::<_, 5, CountingRng>::new(
            tls,
            &mut write_buffer,
            80,
            &mut recv_buffer,
            80,
            mqtt_config,
        );
        client.connect_to_broker().await.unwrap();
        println!("Connected!");

        loop {
            client
                .send_message(
                    "1d7f69f55dae5e84460dee7e62a93156",
                    b"hello there",
                    rust_mqtt::packet::v5::publish_packet::QualityOfService::QoS0,
                    true,
                )
                .await
                .unwrap();
            println!("Sent message");
            Timer::after(Duration::from_millis(1000)).await;
        }
    }
}

#[embassy_executor::task]
async fn connection(mut controller: WifiController<'static>) {
    println!("start connection task");
    println!("Device capabilities: {:?}", controller.get_capabilities());
    loop {
        if esp_wifi::wifi::get_wifi_state() == WifiState::StaConnected {
            // wait until we're no longer connected
            controller.wait_for_event(WifiEvent::StaDisconnected).await;
            Timer::after(Duration::from_millis(5000)).await
        }
        if !matches!(controller.is_started(), Ok(true)) {
            let mut auth_method = AuthMethod::WPA2Personal;
            if PASSWORD.is_empty() {
                auth_method = AuthMethod::None;
            }

            let client_config = Configuration::Client(ClientConfiguration {
                ssid: SSID.try_into().unwrap(),
                password: PASSWORD.try_into().unwrap(),
                auth_method,
                ..Default::default()
            });
            controller.set_configuration(&client_config).unwrap();
            println!("Starting wifi");
            controller.start().await.unwrap();
            println!("Wifi started!");
        }
        println!("About to connect...");

        match controller.connect().await {
            Ok(_) => println!("Wifi connected!"),
            Err(e) => {
                println!("Failed to connect to wifi: {e:?}");
                Timer::after(Duration::from_millis(5000)).await
            }
        }
    }
}

#[embassy_executor::task]
async fn net_task(stack: &'static Stack<WifiDevice<'static, WifiStaDevice>>) {
    stack.run().await
}
