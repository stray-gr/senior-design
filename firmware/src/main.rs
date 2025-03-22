use log::*;
use std::str::FromStr;

use esp_idf_svc::{
    eventloop::EspSystemEventLoop, hal::prelude::Peripherals, nvs::EspDefaultNvsPartition, sys::EspError, wifi::{BlockingWifi, ClientConfiguration, Configuration, EspWifi}
};
use micropb::{
    heapless::{String, Vec},
    MessageDecode, MessageEncode, PbDecoder, PbEncoder
};

// TODO: use include_str! to include SSL certs as strings

#[toml_cfg::toml_config]
pub struct Config {
    #[default("")]
    wifi_ssid: &'static str,
    #[default("")]
    wifi_pass: &'static str,
}

mod example {
    #![allow(clippy::all)]
    #![allow(nonstandard_style, unused, irrefutable_let_patterns)]
    include!("msg.rs");
}

fn init_wifi(
    sys_loop: &EspSystemEventLoop, 
    nvs: &EspDefaultNvsPartition
) -> Result<EspWifi<'static>, EspError> {
    // Grab peripherals for modem
    let periph = Peripherals::take()?;

    // Create wifi client
    let mut esp_wifi = EspWifi::new(
        periph.modem, 
        sys_loop.clone(), 
        Some(nvs.clone())
    )?;
    let mut wifi = BlockingWifi::wrap(
        &mut esp_wifi, 
        sys_loop.clone()
    )?;

    // Config wifi client
    wifi.set_configuration(&Configuration::Client(ClientConfiguration {
        ssid: CONFIG.wifi_ssid.try_into().unwrap(),
        password: CONFIG.wifi_pass.try_into().unwrap(),
        ..Default::default()
    }))?;

    // Connect to wifi
    wifi.start()?;
    wifi.connect()?;
    wifi.wait_netif_up()?;
    info!("Connected to LAN");

    return Ok(esp_wifi);
}

fn main() {
    // Init board
    esp_idf_svc::sys::link_patches();
    esp_idf_svc::log::EspLogger::initialize_default();

    // Grab system peripherals
    // let periph = Peripherals::take().unwrap();
    let sys_loop = EspSystemEventLoop::take().unwrap();
    let nvs = EspDefaultNvsPartition::take().unwrap();

    // Connect to wifi
    init_wifi(&sys_loop, &nvs).unwrap();

    // TODO: Connect to NTP
    // TODO: Create MQTT client 
    // TODO: Poll MQTT broker

    // Create encoder
    // SIZE = 36 byte string for name + 4 byte int32 for age = 40 bytes
    let mut encoder = PbEncoder::new(Vec::<u8, 40>::new());

    // Create message
    let kitty = example::Cat {
        name: String::from_str("Kitty").unwrap(),
        age: 2,
    };

    // Encode message
    kitty.compute_size();
    kitty.encode(&mut encoder).unwrap();

    // Create decoder
    let buf = encoder.into_writer();
    let mut decoder = PbDecoder::new(buf.as_slice());

    // Decode message
    let mut gato = example::Cat::default();
    match gato.decode(&mut decoder, buf.len()) {
        Ok(_) => log::info!("Name: {}, Age: {}", gato.name, gato.age),
        Err(e) => log::error!("{:?}", e),
    }

    log::info!("DONE!");
}
