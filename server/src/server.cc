#include <chrono>
#include <functional>
#include <iostream>
#include <mqtt/client.h>
#include <thread>
#include <vector>

#include "config.h"
#include "server_cb.h"

struct ThreadArgs
{
    std::string tag;
    std::string mqtt_topic;
    std::function<void (std::vector<std::string>&, std::mutex&, std::string)> callback;
    size_t min_batch_size;
    size_t max_batch_size;
    double batch_timeout;
};

std::mutex mtx;

void thread_main(ThreadArgs args) {
    char *MQTT_PASS = std::getenv("MQTT_SERVER_PASS");
    char *MSG_BROKER_URI = std::getenv("MSG_BROKER_URI");
    if ((MQTT_PASS == nullptr) || (MSG_BROKER_URI == nullptr)) {
        mtx.lock();
        std::cout << args.tag << " | Environment variables missing... exiting" << std::endl;
        mtx.unlock();
    }

    mqtt::client user(MSG_BROKER_URI, args.tag, mqtt::create_options(5));
    auto ssl_opts = mqtt::ssl_options_builder()
        .trust_store(MSG_BROKER_CRT)
        .error_handler([](const std::string& err) { std::cerr << err << std::endl; })
        .finalize();

    auto conn_opts = mqtt::connect_options_builder()
        .automatic_reconnect(std::chrono::seconds(1), std::chrono::seconds(15)) // 2**0 + ... + 2**3 = 15
        .clean_start()
        .mqtt_version(5)
        .ssl(std::move(ssl_opts))
        .user_name(MQTT_SERVER_USER)
        .password(MQTT_PASS)
        .finalize();

    try {
        mtx.lock();
        mqtt::connect_response resp = user.connect(conn_opts);
        std::cout << args.tag << " | Connected to " << MSG_BROKER_URI << std::endl;
        mtx.unlock();

        if (!resp.is_session_present()) {
			mqtt::subscribe_options sub_opts;
			mqtt::properties props;
			user.subscribe(args.mqtt_topic, 1, sub_opts, props);
        }

        mtx.lock();
        std::cout << args.tag << " | Subscribed to " << args.mqtt_topic << std::endl;
        mtx.unlock();

        std::vector<std::string> pbuf_str_vec;
        std::chrono::time_point<std::chrono::system_clock> t0, t1;
        std::chrono::duration<double> dt;

        t0 = std::chrono::system_clock::now();

        while(true) { 
            // Try consuming a message
            mqtt::const_message_ptr msg;
            if (user.try_consume_message(&msg)) {
                std::string pbuf_str = msg->get_payload_str();
                pbuf_str_vec.push_back(pbuf_str);
            }

            // If batch is empty, start new timeout (reset t0)
            if (pbuf_str_vec.empty()) {
                t0 = std::chrono::system_clock::now();
            }

            // Get current timeout (dt)
            t1 = std::chrono::system_clock::now();
            dt = t1 - t0;

            // Callback if conditions are met
            if ((dt.count() >= args.batch_timeout && pbuf_str_vec.size() >= args.min_batch_size)
                || (pbuf_str_vec.size() >= args.max_batch_size)
            ) {
                args.callback(pbuf_str_vec, mtx, args.tag);
                pbuf_str_vec.clear();
                t0 = std::chrono::system_clock::now();
            }
        }

    }
    catch (const mqtt::exception& err) {
        std::cerr << args.tag << " | " << err.what() << std::endl;
    }
}

int main() {
    ThreadArgs data_args = {
        .tag = "DATA",
        .mqtt_topic = MQTT_DATA_TOPIC,
        .callback = data_callback,
        .min_batch_size = 1,
        .max_batch_size = 2,
        .batch_timeout = 10.0,
    };

    ThreadArgs lwt_args = {
        .tag = "LWT ",
        .mqtt_topic = MQTT_LWT_TOPIC,
        .callback = lwt_callback,
        .min_batch_size = 1,
        .max_batch_size = 2,
        .batch_timeout = 10.0,
    };

    std::thread data_thread(thread_main, data_args);
    std::thread lwt_thread(thread_main, lwt_args);

    data_thread.join();
    lwt_thread.join();
}