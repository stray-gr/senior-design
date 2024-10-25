#![no_std]
#![no_main]

extern crate alloc;
use embedded_tls::blocking::*;
use esp_alloc as _;
use esp_backtrace as _;
use esp_hal::{
    peripheral::Peripheral,
    prelude::*,
    rng::{Rng, Trng},
    time::{self, Duration},
};
use esp_println::{print, println};
use esp_wifi::{
    wifi::{
        utils::create_network_interface, AccessPointInfo, AuthMethod, ClientConfiguration,
        Configuration, WifiError, WifiStaDevice,
    },
    wifi_interface::WifiStack,
    EspWifiInitFor, EspWifiInitialization,
};
use smoltcp::iface::SocketStorage;
use smoltcp::wire::IpAddress;
use smoltcp::wire::Ipv4Address;

const SSID: &str = env!("SSID");
const PASSWORD: &str = env!("PASSWORD");

#[entry]
fn main() -> ! {
    esp_alloc::heap_allocator!(72 * 1024);

    let mut p = esp_hal::init({
        let mut config = esp_hal::Config::default();
        config.cpu_clock = CpuClock::max();
        config
    });

    // Initialize the timers used for Wifi
    // ANCHOR: wifi_init
    let timg0 = esp_hal::timer::timg::TimerGroup::new(p.TIMG0);
    let init: EspWifiInitialization;
    unsafe {
        init = esp_wifi::init(
            EspWifiInitFor::Wifi,
            timg0.timer0,
            Rng::new(p.RNG.clone_unchecked()),
            p.RADIO_CLK,
        )
        .unwrap();
    }
    // ANCHOR_END: wifi_init

    // Configure Wifi
    // ANCHOR: wifi_config
    let mut wifi = p.WIFI;
    let mut socket_set_entries: [SocketStorage; 3] = Default::default();
    let (iface, device, mut controller, sockets) =
        create_network_interface(&init, &mut wifi, WifiStaDevice, &mut socket_set_entries).unwrap();
    // ANCHOR_END: wifi_config

    let mut auth_method = AuthMethod::WPA2Personal;
    if PASSWORD.is_empty() {
        auth_method = AuthMethod::None;
    }

    // ANCHOR: client_config_start
    let client_config = Configuration::Client(ClientConfiguration {
        // ANCHOR_END: client_config_start
        ssid: SSID.try_into().unwrap(),
        password: PASSWORD.try_into().unwrap(),
        auth_method,
        ..Default::default() // ANCHOR: client_config_end
    });

    let res = controller.set_configuration(&client_config);
    println!("Wi-Fi set_configuration returned {:?}", res);
    // ANCHOR_END: client_config_end

    // ANCHOR: wifi_connect
    controller.start().unwrap();
    println!("Is wifi started: {:?}", controller.is_started());

    println!("Start Wifi Scan");
    let res: Result<(heapless::Vec<AccessPointInfo, 10>, usize), WifiError> = controller.scan_n();
    if let Ok((res, _count)) = res {
        for ap in res {
            println!("{:?}", ap);
        }
    }

    println!("{:?}", controller.get_capabilities());
    println!("Wi-Fi connect: {:?}", controller.connect());

    // Wait to get connected
    println!("Wait to get connected");
    loop {
        let res = controller.is_connected();
        match res {
            Ok(connected) => {
                if connected {
                    break;
                }
            }
            Err(err) => {
                println!("{:?}", err);
                panic!();
            }
        }
    }
    println!("{:?}", controller.is_connected());
    // ANCHOR_END: wifi_connect

    // ANCHOR: ip
    // Wait for getting an ip address
    let now = || time::now().duration_since_epoch().to_millis();
    let wifi_stack = WifiStack::new(iface, device, sockets, now);
    println!("Wait to get an ip address");
    loop {
        wifi_stack.work();

        if wifi_stack.is_iface_up() {
            println!("got ip {:?}", wifi_stack.get_ip_info());
            break;
        }
    }
    // ANCHOR_END: ip

    println!("Start busy loop on main");

    let mut rx_buffer = [0u8; 4096];
    let mut tx_buffer = [0u8; 4096];
    let mut socket = wifi_stack.get_socket(&mut rx_buffer, &mut tx_buffer);

    println!("Making HTTP request");
    socket.work();

    socket
        .open(IpAddress::Ipv4(Ipv4Address::new(93, 184, 215, 14)), 443)
        .unwrap();
    println!("TCP connected");

    let mut read_record_buffer = [0; 16384];
    let mut write_record_buffer = [0; 16384];
    let config: embedded_tls::TlsConfig<'_, Aes128GcmSha256> =
        TlsConfig::new().with_server_name("example.com");
    let mut tls = TlsConnection::new(socket, &mut read_record_buffer, &mut write_record_buffer);

    let mut idk = Trng::new(p.RNG, p.ADC1);
    tls.open::<Trng, NoVerify>(TlsContext::new(&config, &mut idk))
        .expect("error establishing TLS connection");
    tls.write(b"GET / HTTP/1.0\r\nHost: www.example.com\r\n\r\n")
        .unwrap();
    tls.flush().unwrap();

    // ANCHOR: reponse
    let deadline = time::now() + Duration::secs(20);
    let mut buffer = [0u8; 4096];
    while let Ok(len) = tls.read(&mut buffer) {
        let to_print = unsafe { core::str::from_utf8_unchecked(&buffer[..len]) };
        print!("{}", to_print);

        if time::now() > deadline {
            println!("Timeout");
            break;
        }
    }
    println!();
    // ANCHOR_END: reponse

    // ANCHOR: socket_close
    let _ = tls.close();
    panic!()
    // ANCHOR_END: socket_close
}
