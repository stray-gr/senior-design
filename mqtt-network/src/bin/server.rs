use rumqttc::{Client, MqttOptions, Packet, QoS};
use std::{thread, time::Duration};

/* TODO:
 * - Update messages to use MSG struct from model in lib.rs
 * - Add JSON serialization to MSG structs using serde
 * - Look into using authentication without encryption... are credentials plain text?
 * - For more TODOs, look down below
 */


fn main() {
    println!("Starting server...");
    let timer_topic = String::from("timer"); // Publisher
    let data_topic  = String::from("data");  // Subscriber

    let mut mqttoptions = MqttOptions::new("server", "localhost", 1883);
    mqttoptions.set_keep_alive(Duration::from_secs(5));

    let (mut client, mut connection) = Client::new(mqttoptions, 10);
    client.subscribe(&data_topic, QoS::AtMostOnce).unwrap();

    thread::spawn(move || loop {
        client.publish(&timer_topic, QoS::AtLeastOnce, false, "").unwrap();
        thread::sleep(Duration::from_secs(1));
    });

    // REQUIRED: Handle each event in an event loop
    for (_, notification) in connection.iter().enumerate() {
        match notification {
            Ok(rumqttc::Event::Outgoing(_)) => {
                println!("Sending data request to clients");
            },
            Ok(rumqttc::Event::Incoming(Packet::Publish(msg))) => {
                /* TODO: 
                 * - Extract the data from JSON in the newly spawned thread
                 * - Clean the data, then insert it into the DB 
                 * - Export this logic to a separate function, which gets passed to the thread 
                 * - Add unit tests for the thread's function */
                if msg.topic == data_topic {
                    thread::spawn(move || {
                        let data = std::str::from_utf8(&msg.payload).unwrap();
                        println!("Data recieved from {}: {}", "client", data);
                    });
                }
            },
            Err(e) => {
                println!("ERROR: {:?}", e);
            }
            _ => {}, // Ignore everything else
        }
    }
}
