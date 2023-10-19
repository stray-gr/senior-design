use rumqttc::{Client, MqttOptions, Packet, QoS};
use std::time::Duration;
use std::thread;

/* EXAMPLE */
fn main() {
    let hello_topic = String::from("hello");

    let mut mqttoptions = MqttOptions::new("test", "localhost", 1883);
    mqttoptions.set_keep_alive(Duration::from_secs(5));

    let (mut client, mut connection) = Client::new(mqttoptions, 10);
    client.subscribe(&hello_topic, QoS::AtMostOnce).unwrap();

    thread::spawn(move || for i in 0..10 {
        client.publish(&hello_topic, QoS::AtLeastOnce, false, format!("Hello no. {}", i)).unwrap();
        thread::sleep(Duration::from_secs(1));
    });

    // REQUIRED: Handle each event in an event loop
    for (_, notification) in connection.iter().enumerate() {
        match notification {
            Ok(rumqttc::Event::Incoming(Packet::Publish(msg))) => {
                if msg.topic == "hello" {
                    let data = std::str::from_utf8(&msg.payload).unwrap();
                    println!("{}", data);
                }
            },
            Err(e) => {
                println!("ERROR: {:?}", e);
            }
            _ => {}, // Ignore everything else
        }
    }
}
