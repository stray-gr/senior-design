#include <cstdlib>
#include <iostream>

// g++ msg.pb.cc client/client.cc -pthread -lprotobuf -lpaho-mqttpp3 -lpaho-mqtt3as -lssl -lcrypto -o bin/client
// LD_LIBRARY_PATH=/usr/local/lib ./client
#include "config.h"
#include "mqtt/client.h" 
#include "../msg.pb.h"

int main() {
    mqtt::client user(MSG_BROKER_URI, "1234321", mqtt::create_options(5));
    auto ssl_opts = mqtt::ssl_options_builder()
        .trust_store(MSG_BROKER_CRT)
        .error_handler([](const std::string& err) { std::cerr << err << std::endl; })
        .finalize();
    auto conn_opts = mqtt::connect_options_builder()
        .automatic_reconnect(std::chrono::seconds(1), std::chrono::seconds(15)) // 2**0 + ... + 2**3 = 15
        .clean_start()
        .mqtt_version(5)
        .ssl(ssl_opts)
        .finalize();

    try {
        mqtt::connect_response resp = user.connect(conn_opts);
        std::cout << "Connected to " << MSG_BROKER_URI << std::endl;

        srand(time(0));

        Cat kit;
        kit.set_name("KITTY");
        kit.set_age((rand() % 10) + 1);

        auto msg = mqtt::make_message(MQTT_DATA_TOPIC, kit.SerializeAsString());
		msg->set_qos(1);
		user.publish(msg);
		std::cout << "DONE" << std::endl;

    }
    catch (const mqtt::exception& err) {
        std::cerr << err.what() << std::endl;
    }
}
