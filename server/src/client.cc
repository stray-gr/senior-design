#include <cstdlib>
#include <iostream>
#include <mqtt/client.h>
#include <sys/time.h>

#include "config.h"
#include "msg.pb.h"

const std::string DEVICE{"client"};

int main() {
    char *MQTT_PASS = std::getenv("MQTT_CLIENT_PASS");
    char *MSG_BROKER_URI = std::getenv("MSG_BROKER_URI");
    if ((MQTT_PASS == nullptr) || (MSG_BROKER_URI == nullptr)) {
        std::cout << "Environment variables missing... exiting" << std::endl;
    }

    LWT lwt_msg;
    lwt_msg.set_device(DEVICE);

    mqtt::client user(MSG_BROKER_URI, MQTT_CLIENT_USER, mqtt::create_options(5));
    auto lwt_pbuf_msg = mqtt::message(MQTT_LWT_TOPIC, lwt_msg.SerializeAsString(), 1, true);
    auto ssl_opts = mqtt::ssl_options_builder()
        .trust_store(MSG_BROKER_CRT)
        .error_handler([](const std::string& err) { std::cerr << err << std::endl; })
        .finalize();

    auto conn_opts = mqtt::connect_options_builder()
        .automatic_reconnect(std::chrono::seconds(1), std::chrono::seconds(15)) // 2**0 + ... + 2**3 = 15
        .clean_start()
        .mqtt_version(5)
        .ssl(std::move(ssl_opts))
        .will(std::move(lwt_pbuf_msg))
        .user_name(MQTT_CLIENT_USER)
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
                struct timeval t;
                gettimeofday(&t, NULL);

                Data sensor_data;
                sensor_data.set_device(DEVICE);
                sensor_data.set_temp(rand() % 100);
                sensor_data.set_rh(55.5);
                sensor_data.set_epoch(t.tv_sec);

                auto msg = mqtt::make_message(MQTT_DATA_TOPIC, sensor_data.SerializeAsString(), 1, false);
                user.publish(msg);
            }
        }
    }
    catch (const mqtt::exception& err) {
        std::cerr << err.what() << std::endl;
    }
}
