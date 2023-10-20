use actix_files::{Files, NamedFile};
use actix_web::{middleware::Logger, App, HttpServer, Responder, get};
use actix_web_lab::sse;
use rumqttc::{Client, MqttOptions, Packet, QoS};
use std::{
    sync::OnceLock,
    sync::RwLock,
    thread,
    time::Duration,
};

fn current_txt() -> &'static RwLock<String> {
    let default: String = String::from("Battery level recieved from client: ???");
    static TXT: OnceLock<RwLock<String>> = OnceLock::new();
    return TXT.get_or_init(|| RwLock::new(default));
}

#[get("/")]
async fn index() -> impl Responder {
    NamedFile::open_async("./static/index.html").await.unwrap()
}

#[get("/sse")]
async fn sse_broadcast() -> impl Responder {
    let (sender, sse_stream) = sse::channel(10);
    let inner_txt = current_txt().read().unwrap().to_string();

    match sender.send(sse::Data::new(inner_txt).event("update")).await {
        Err(e) => {
            log::error!("{e:?}");
        },
        _ => (),
    }

    return sse_stream;
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    env_logger::init_from_env(env_logger::Env::new().default_filter_or("info"));
    log::info!("Starting HTTP server at http://localhost:8080");
    
    thread::spawn(move || {
        let data_topic  = String::from("data");  // Subscriber

        let mut mqttoptions = MqttOptions::new("webserver", "localhost", 1883);
        mqttoptions.set_keep_alive(Duration::from_secs(5));

        let (mut client, mut connection) = Client::new(mqttoptions, 10);
        client.subscribe(&data_topic, QoS::AtMostOnce).unwrap();

        /* REQUIRED: Handle each event in an event loop */ 
        for (_, notification) in connection.iter().enumerate() {
            match notification {
                Ok(rumqttc::Event::Incoming(Packet::Publish(msg))) => {
                    if msg.topic == data_topic {
                        let data = String::from_utf8(msg.payload.to_vec()).unwrap();
                        let mut inner_txt = current_txt().write().unwrap();
                        *inner_txt = data;
                    }
                },
                Err(e) => {
                    log::error!("{e:?}");
                }
                _ => {}, // Ignore everything else
            }
        }
    });

    HttpServer::new(move || {
        App::new()
            .service(index)
            .service(sse_broadcast)
            .service(Files::new("/static", "./static"))
            .wrap(Logger::default())
        })
        .workers(2)
        .bind(("127.0.0.1", 8080))?
        .run()
        .await
}