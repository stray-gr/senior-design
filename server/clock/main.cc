#include <chrono>
#include <iostream>
#include <mqtt/client.h>

#include "config.h"

int main() {
    mqtt::client user(MSG_BROKER_URI, MQTT_USER, mqtt::create_options(5));
    auto ssl_opts = mqtt::ssl_options_builder()
        .trust_store(MSG_BROKER_CRT)
        .error_handler([](const std::string& err) { std::cerr << err << std::endl; })
        .finalize();

    auto conn_opts = mqtt::connect_options_builder()
        .automatic_reconnect(std::chrono::seconds(1), std::chrono::seconds(15)) // 2**0 + ... + 2**3 = 15
        .clean_start()
        .mqtt_version(5)
        .ssl(std::move(ssl_opts))
        .user_name(MQTT_USER)
        .password(MQTT_PASS)
        .finalize();

    try {
        mqtt::connect_response resp = user.connect(conn_opts);
        std::cout << "Connected to " << MSG_BROKER_URI << std::endl;

        while(true) {
            auto msg = mqtt::make_message(MQTT_PULSE_TOPIC, "", 1, false);
            user.publish(msg);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    catch (const mqtt::exception& err) {
        std::cerr << err.what() << std::endl;
    }
}
