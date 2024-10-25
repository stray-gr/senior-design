use embedded_io_adapters::tokio_1::FromTokio;
use rust_mqtt::{
    client::{client, client_config},
    packet::v5::publish_packet,
    utils::rng_generator::CountingRng,
};
use rustls_rustcrypto::provider;
use std::path::PathBuf;
use std::{io, net::ToSocketAddrs, sync::Arc, time::Duration};
use tokio::net::TcpStream;
use tokio_rustls::{client::TlsStream, rustls, TlsConnector};

struct Options {
    host: String,
    port: u16,
    domain: Option<String>,
    cafile: Option<PathBuf>,
}

#[tokio::main]
async fn main() -> Result<(), io::Error> {
    // It is necessary to call this function once. Otherwise some patches to the runtime
    // implemented by esp-idf-sys might not link properly. See https://github.com/esp-rs/esp-idf-template/issues/71
    esp_idf_svc::sys::link_patches();

    // Bind the log crate to the ESP Logging facilities
    esp_idf_svc::log::EspLogger::initialize_default();

    log::info!("Hello, world!");

    /* TLS */
    let options = Options {
        host: String::from("localhost"),
        port: 8883,
        domain: None,
        cafile: None,
    };

    let addr = (options.host.as_str(), options.port)
        .to_socket_addrs()?
        .next()
        .ok_or_else(|| io::Error::from(io::ErrorKind::NotFound))?;
    let domain = options.domain.unwrap_or(options.host);

    let mut root_cert_store = rustls::RootCertStore::empty();
    // if let Some(cafile) = &options.cafile {
    //     root_cert_store.add();
    // }

    let config = rustls::ClientConfig::builder_with_provider(provider().into())
        .with_safe_default_protocol_versions()
        .unwrap()
        .with_root_certificates(rustls::RootCertStore::empty())
        .with_no_client_auth();

    let connector = TlsConnector::from(Arc::new(config));
    let stream = TcpStream::connect(&addr).await?;
    let domain = rustls::pki_types::ServerName::try_from(domain.as_str())
        .map_err(|_| io::Error::new(io::ErrorKind::InvalidInput, "invalid dnsname"))?
        .to_owned();

    let stream = connector.connect(domain, stream).await?;
    let idk = FromTokio::<TlsStream<TcpStream>>::new(stream);

    // let config = rustls::ClientConfig::builder_with_provider(provider().into())
    //     .with_safe_default_protocol_versions()
    //     .unwrap()
    //     .with_root_certificates(rustls::RootCertStore::empty())
    //     .with_no_client_auth();

    // let mut conn = rustls::ClientConnection::new(Arc::new(config), "localhost".into()).unwrap();
    // let mut sock = TcpStream::connect("127.0.0.1:443").await.unwrap();
    // let mut tls = rustls::Stream::new(&mut conn, &mut sock);
    // let idk = FromTokio::<rustls::Stream>::new(tls);

    /* MQTT PUB */
    let mut mqtt_config =
        client_config::ClientConfig::new(client_config::MqttVersion::MQTTv5, CountingRng(20000));

    mqtt_config.add_client_id("dev2");
    mqtt_config.add_username("dev2");
    mqtt_config.add_password("PASSword");

    mqtt_config.add_max_subscribe_qos(publish_packet::QualityOfService::QoS1);
    mqtt_config.max_packet_size = 4096;

    let mut mqtt_rx_buffer = [0; 4096];
    let mut mqtt_tx_buffer = [0; 4096];

    let mut client = client::MqttClient::<_, 5, _>::new(
        idk,
        &mut mqtt_tx_buffer,
        4096,
        &mut mqtt_rx_buffer,
        4096,
        mqtt_config,
    );

    client.connect_to_broker().await.unwrap();

    loop {
        client
            .send_message(
                "hello",
                b"hello2",
                publish_packet::QualityOfService::QoS0,
                true,
            )
            .await
            .unwrap();
        tokio::time::sleep(Duration::from_millis(500)).await;
    }
}
