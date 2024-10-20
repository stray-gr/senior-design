use ntex::time::{sleep, Millis, Seconds};
use ntex::{service::fn_service, util::Ready};
use ntex_mqtt::v5;

#[derive(Debug)]
struct Error;

impl std::convert::TryFrom<Error> for v5::PublishAck {
    type Error = Error;

    fn try_from(err: Error) -> Result<Self, Self::Error> {
        Err(err)
    }
}

#[derive(Debug)]
#[toml_cfg::toml_config]
pub struct Config {
    #[default("")]
    user: &'static str,
    #[default("")]
    pass: &'static str,
}

#[ntex::main]
async fn main() -> std::io::Result<()> {
    // It is necessary to call this function once. Otherwise some patches to the runtime
    // implemented by esp-idf-sys might not link properly. See https://github.com/esp-rs/esp-idf-template/issues/71
    esp_idf_svc::sys::link_patches();

    // Bind the log crate to the ESP Logging facilities
    esp_idf_svc::log::EspLogger::initialize_default();

    dbg!(CONFIG);

    // ssl connector
    let mut builder = ssl::SslConnector::builder(ssl::SslMethod::tls()).unwrap();
    builder.set_verify(ssl::SslVerifyMode::NONE);

    // connect to server
    let client = v5::client::MqttConnector::new("127.0.0.1:8883")
        .connector(SslConnector::new(builder.build()))
        .client_id(CONFIG.user)
        .username(CONFIG.user)
        .password(CONFIG.pass)
        .keep_alive(Seconds(60))
        .connect()
        .await
        .unwrap();

    let sink = client.sink();

    // handle incoming publishes
    ntex::rt::spawn(client.start(fn_service(
        |control: v5::client::Control<Error>| match control {
            v5::client::Control::Publish(publish) => {
                log::info!(
                    "incoming publish: {:?} -> {:?} payload {:?}",
                    publish.packet().packet_id,
                    publish.packet().topic,
                    publish.packet().payload
                );
                Ready::Ok(publish.ack(v5::codec::PublishAckReason::Success))
            }
            v5::client::Control::Disconnect(msg) => {
                log::warn!("Server disconnecting: {:?}", msg);
                Ready::Ok(msg.ack())
            }
            v5::client::Control::Error(msg) => {
                log::error!("Codec error: {:?}", msg);
                Ready::Ok(msg.ack(v5::codec::DisconnectReasonCode::UnspecifiedError))
            }
            v5::client::Control::ProtocolError(msg) => {
                log::error!("Protocol error: {:?}", msg);
                Ready::Ok(msg.ack())
            }
            v5::client::Control::PeerGone(msg) => {
                log::warn!("Peer closed connection: {:?}", msg.error());
                Ready::Ok(msg.ack())
            }
            v5::client::Control::Closed(msg) => {
                log::warn!("Server closed connection: {:?}", msg);
                Ready::Ok(msg.ack())
            }
        },
    )));

    // subscribe to topic
    sink.subscribe(None)
        .topic_filter(
            "pulse".into(),
            v5::codec::SubscriptionOptions {
                qos: v5::codec::QoS::AtLeastOnce,
                no_local: false,
                retain_as_published: false,
                retain_handling: v5::codec::RetainHandling::AtSubscribe,
            },
        )
        .send()
        .await
        .unwrap();

    Ok(())
}
