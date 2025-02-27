#include <chrono>
#include <iostream>
#include <mqtt/client.h>

#include "config.h"

int main() {
    char *MQTT_PASS = std::getenv("MQTT_CLOCK_PASS");
    char *MSG_BROKER_URI = std::getenv("VIRTUAL_BROKER_URI");
    if ((MQTT_PASS == nullptr) || (MSG_BROKER_URI == nullptr)) {
        std::cout << "Environment variables missing... exiting" << std::endl;
    }

    mqtt::client user(MSG_BROKER_URI, MQTT_CLOCK_USER, mqtt::create_options(5));
    auto conn_opts = mqtt::connect_options_builder()
        .automatic_reconnect(std::chrono::seconds(1), std::chrono::seconds(15)) // 2**0 + ... + 2**3 = 15
        .clean_start()
        .mqtt_version(5)
        .user_name(MQTT_CLOCK_USER)
        .password(MQTT_PASS)
        .finalize();

    try {
        mqtt::connect_response resp = user.connect(conn_opts);
        std::cout << "Connected to " << MSG_BROKER_URI << std::endl;

        // while(true) {
        //     auto msg = mqtt::make_message(MQTT_PULSE_TOPIC, "", 1, false);
        //     user.publish(msg);
        //     std::this_thread::sleep_for(std::chrono::milliseconds(500));
        // }

        for (int n = 0; n < 5; n++) {
            auto msg = mqtt::make_message(MQTT_PULSE_TOPIC, "", 1, false);
            user.publish(msg);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    catch (const mqtt::exception& err) {
        std::cerr << err.what() << std::endl;
    }
}
