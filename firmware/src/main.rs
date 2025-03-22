use log::*;
use std::str::FromStr;

use esp_idf_svc::{
    eventloop::EspSystemEventLoop, hal::prelude::Peripherals, mqtt::client::{
        EspMqttClient, EspMqttConnection, EventPayload, LwtConfiguration, MqttClientConfiguration, MqttProtocolVersion, QoS
    }, nvs::EspDefaultNvsPartition, sntp, sys::EspError, tls::X509, wifi::{
        AuthMethod, BlockingWifi, ClientConfiguration, Configuration, EspWifi
    }
};
use micropb::{
    heapless::{String, Vec},
    MessageEncode, PbEncoder
};

#[toml_cfg::toml_config]
pub struct Config {
    #[default("")]
    wifi_ssid: &'static str,
    #[default("")]
    wifi_pass: &'static str,

    #[default("")]
    broker_uri: &'static str,
    #[default("")]
    mqtt_user: &'static str,
    #[default("")]
    mqtt_pass: &'static str,

    #[default("")]
    connect_topic: &'static str,
    #[default("")]
    pulse_topic: &'static str,
    #[default("")]
    data_topic: &'static str,
    #[default("")]
    lwt_topic: &'static str,
    #[default(0)]
    lwt_delay: i64,
}

const CA_CERT: &str = concat!(include_str!("mosquitto.org.crt"), '\0');

mod msg {
    #![allow(clippy::all)]
    #![allow(nonstandard_style, unused, irrefutable_let_patterns)]
    include!("msg.rs");
}

fn main() {
    // Init board
    esp_idf_svc::sys::link_patches();
    esp_idf_svc::log::EspLogger::initialize_default();

    // Connect to wifi
    let _wifi = init_wifi().unwrap();
    info!("Connected to wifi");

    // Set up SNTP
    let _sntp = sntp::EspSntp::new_default().unwrap();
    info!("Set up SNTP");

    // Create LWT message
    let lwt_msg= msg::LWT {
        device: String::from_str(CONFIG.mqtt_user).unwrap(),
        delay: CONFIG.lwt_delay,
    };

    // Encode LWT message
    let mut lwt_encoder = PbEncoder::new(Vec::<u8, 44>::new());
    lwt_msg.compute_size();
    lwt_msg.encode(&mut lwt_encoder).unwrap();
    let lwt_payload = lwt_encoder.into_writer();

    // Create MQTT client 
    let (mut mqtt_client, mut mqtt_conn) = EspMqttClient::new(
        CONFIG.broker_uri,
        &MqttClientConfiguration {
            protocol_version: Some(MqttProtocolVersion::V3_1_1),
            lwt: Some(LwtConfiguration{
                topic: CONFIG.lwt_topic,
                payload: &lwt_payload,
                qos: QoS::AtLeastOnce,
                retain: false,
            }),
            buffer_size: 1024,
            out_buffer_size: 1024,
            // username: Some(CONFIG.mqtt_user),
            // password: Some(CONFIG.mqtt_pass),
            server_certificate: Some(X509::pem_until_nul(CA_CERT.as_bytes())),
            ..Default::default()
        }
    ).unwrap();
    info!("MQTT Client created");

    poll_mqtt(&mut mqtt_client, &mut mqtt_conn).unwrap();

}

fn init_wifi() -> Result<BlockingWifi<EspWifi<'static>>, EspError> {
    // Grab system peripherals
    let periph = Peripherals::take().unwrap();
    let sys_loop = EspSystemEventLoop::take().unwrap();
    let nvs = EspDefaultNvsPartition::take().unwrap();

    // Create wifi client
    let mut wifi_client = BlockingWifi::wrap(
        EspWifi::new(periph.modem, sys_loop.clone(), Some(nvs))?, 
        sys_loop
    )?;


    // Config wifi client
    wifi_client.set_configuration(&Configuration::Client(ClientConfiguration {
        ssid: CONFIG.wifi_ssid.try_into().unwrap(),
        bssid: None,
        auth_method: AuthMethod::WPA2Personal,
        password: CONFIG.wifi_pass.try_into().unwrap(),
        channel: None,
        ..Default::default()
    }))?;

    // Connect to wifi
    wifi_client.start()?;
    wifi_client.connect()?;
    wifi_client.wait_netif_up()?;

    // Return client to calling scope
    return Ok(wifi_client);
}

fn poll_mqtt(client: &mut EspMqttClient<'_>, conn: &mut EspMqttConnection) -> Result<(), EspError> {
    std::thread::scope(|s| {
        // Iterate over connection events or exit on fail
        std::thread::Builder::new().stack_size(6000).spawn_scoped(s, move || {
            while let Ok(event) = conn.next() {
                match event.payload() {
                    // On connection to broker, send a connect message
                    EventPayload::Connected(true) => {
                        let payload = create_connect_msg().unwrap();
                        client.enqueue(
                            CONFIG.connect_topic, 
                            QoS::AtLeastOnce, 
                            false, 
                            &payload
                        ).unwrap();
                    }

                    // Handle subscription message event by topic
                    EventPayload::Received { 
                        id: _,
                        topic, 
                        data: _, 
                        details : _,
                    } => {
                        match topic {
                            // Topic exists
                            Some(topic) => {
                                info!("Recieved message from {}", topic);
                                if topic == CONFIG.pulse_topic {
                                    if let Ok(payload) = create_sensor_data() {
                                        client.enqueue(
                                            CONFIG.data_topic, 
                                            QoS::AtLeastOnce, 
                                            false, 
                                            &payload
                                        ).unwrap();
                                        info!("Sent sensor data message")
                                    } else {
                                        error!("Unable to encode sensor data message")
                                    }
                                }
                            },

                            // Topic DNE
                            None => warn!("Recieved message w/ no topic name"),
                        }
                    },
                    
                    // Handle all other events
                    _ => info!("{}", event.payload()),
                }
            }
        }).unwrap();

        Ok(())
    })
}

fn create_connect_msg() -> Result<Vec<u8, 36>, EspError> {
    // Create connect message
    let conn_msg = msg::Connect {
        device: String::from_str(CONFIG.mqtt_user).unwrap()
    };

    // Encode connect message
    let mut encoder = PbEncoder::new(Vec::<u8, 36>::new());
    conn_msg.compute_size();
    conn_msg.encode(&mut encoder).unwrap();
    let payload = encoder.into_writer();

    Ok(payload)
}

fn create_sensor_data() -> Result<Vec<u8, 52>, EspError> {
    // Create sensor data message
    let data_msg = msg::SensorData {
        device: String::from_str(CONFIG.mqtt_user).unwrap(),
        temp: 30.1,
        rh: 50.5,
        epoch: 10,
    };

    // Encode connect message
    let mut encoder = PbEncoder::new(Vec::<u8, 52>::new());
    data_msg.compute_size();
    data_msg.encode(&mut encoder).unwrap();
    let payload = encoder.into_writer();

    Ok(payload)
}