use rumqttc::{Client, MqttOptions, Packet, QoS};
use std::time::Duration;

/* TODO:
 * - Port to ESP32
 * - Update messages to use MSG struct from model in lib.rs
 * - Add JSON serialization to MSG structs using serde
 * - Create a struct for storing mqtt host, port, and credentials via toml_cfg
 * - Create a struct for storing wifi ssid and password via toml_cfg
 * - Look into using authentication without encryption... are credentials plain text?
 */

fn main() {
    println!("Starting client...");
    let timer_topic = String::from("timer"); // Subscriber
    let data_topic  = String::from("data");  // Publisher

    let mut mqttoptions = MqttOptions::new("client", "localhost", 1883);
    mqttoptions.set_keep_alive(Duration::from_secs(5));

    let (mut client, mut connection) = Client::new(mqttoptions, 10);
    client.subscribe(&timer_topic, QoS::AtMostOnce).unwrap();

    /* REQUIRED: Handle each event in an event loop */ 
    for (_, notification) in connection.iter().enumerate() {
        match notification {
            Ok(rumqttc::Event::Incoming(Packet::Publish(msg))) => {
                if msg.topic == timer_topic {
                    println!("Request recieved, sending data to server");
                    client.publish(&data_topic, QoS::AtLeastOnce, false, "random data").unwrap();
                }
            },
            Err(e) => {
                println!("ERROR: {:?}", e);
            }
            _ => {}, // Ignore everything else
        }
    }
}
