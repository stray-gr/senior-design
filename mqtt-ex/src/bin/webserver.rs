use rumqttc::{Client, MqttOptions, Packet, QoS};
use std::time::Duration;

/* TODO: 
 * - Figure out mqtt and actix integration. Need to send power
 *   level warnings from the data MQTT topic to the control 
 *   panel via WebSocket 
 */

fn main() {
    println!("Starting webserver...");
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
                    let data = std::str::from_utf8(&msg.payload).unwrap();
                    println!("Battery level recieved from {}: {}", "client", data);
                }
            },
            Err(e) => {
                println!("ERROR: {:?}", e);
            }
            _ => {}, // Ignore everything else
        }
    }
}