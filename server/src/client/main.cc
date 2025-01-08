#include <cstdlib>
#include <iostream>

// LD_LIBRARY_PATH=/usr/local/lib server/bin/client
#include "config.h"
#include "mqtt/client.h" 
#include "../msg.pb.h"

const std::string LWT_MSG{"Bye Bye"};

int main() {
    mqtt::client user(MSG_BROKER_URI, MQTT_USER, mqtt::create_options(5));
    auto lwt_msg = mqtt::message(MQTT_LWT_TOPIC, LWT_MSG, 1, true);
    auto ssl_opts = mqtt::ssl_options_builder()
        .trust_store(MSG_BROKER_CRT)
        .error_handler([](const std::string& err) { std::cerr << err << std::endl; })
        .finalize();

    auto conn_opts = mqtt::connect_options_builder()
        .automatic_reconnect(std::chrono::seconds(1), std::chrono::seconds(15)) // 2**0 + ... + 2**3 = 15
        .clean_start()
        .mqtt_version(5)
        .ssl(std::move(ssl_opts))
        .will(std::move(lwt_msg))
        .user_name(MQTT_USER)
        .password(MQTT_PASS)
        .finalize();

    srand(time(0));

    try {
        mqtt::connect_response resp = user.connect(conn_opts);
        std::cout << "Connected to " << MSG_BROKER_URI << std::endl;

        if (!resp.is_session_present()) {
			mqtt::subscribe_options sub_opts;
			mqtt::properties props;
			user.subscribe(MQTT_PULSE_TOPIC, 1, sub_opts, props);
        }

        std::cout << "Subscribed to " << MQTT_PULSE_TOPIC << std::endl;

        while(true) {
            // Block until new message can be consumed
            auto pulse = user.consume_message();
            if (pulse) {
                Cat kit;
                kit.set_name("KITTY");
                kit.set_age((rand() % 10) + 1);

                auto msg = mqtt::make_message(MQTT_DATA_TOPIC, kit.SerializeAsString(), 1, false);
                user.publish(msg);
            }
        }
    }
    catch (const mqtt::exception& err) {
        std::cerr << err.what() << std::endl;
    }
}
