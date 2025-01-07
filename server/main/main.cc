#include <array>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

// g++ msg.pb.cc main/main.cc -pthread -lprotobuf -lpaho-mqttpp3 -lpaho-mqtt3as -lssl -lcrypto -o bin/main
// LD_LIBRARY_PATH=/usr/local/lib ./main
#include "config.h"
#include "mqtt/client.h" 
#include "../msg.pb.h"

std::mutex mtx;

struct ThreadArgs
{
    std::string mqtt_topic;
    double batch_timeout;
    int min_batch_size;
    int max_batch_size;
    std::function<void (std::vector<std::string>&, std::mutex&)> callback;
};

void thread_main(ThreadArgs args) {
    mqtt::client user(MSG_BROKER_URI, MQTT_USER, mqtt::create_options(5));
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

        mtx.lock();
        std::cout << "Connected to " << MSG_BROKER_URI << std::endl;
        mtx.unlock();

        if (!resp.is_session_present()) {
			mqtt::subscribe_options sub_opts;
			mqtt::properties props;
			user.subscribe(args.mqtt_topic, 1, sub_opts, props);
        }

        mtx.lock();
        std::cout << "Subscribed to " << args.mqtt_topic << std::endl;
        mtx.unlock();

        std::vector<std::string> pbuf_str_vec;
        std::chrono::time_point<std::chrono::system_clock> t0, t1;
        std::chrono::duration<double> dt;

        t0 = std::chrono::system_clock::now();

        while(true) { 
            mqtt::const_message_ptr msg;

            if (user.try_consume_message(&msg)) {
                // Get new message
                std::string pbuf_str = msg->get_payload_str();
                pbuf_str_vec.push_back(pbuf_str);
            }

            if (pbuf_str_vec.empty()) {
                // Batch is empty, reset timeout
                t0 = std::chrono::system_clock::now();
            }

            // Get dT
            t1 = std::chrono::system_clock::now();
            dt = t1 - t0;

            // Callback if conditions are met
            if ((dt.count() >= args.batch_timeout && pbuf_str_vec.size() >= args.min_batch_size)
                || (pbuf_str_vec.size() >= args.max_batch_size)
            ) {
                args.callback(pbuf_str_vec, mtx);
                pbuf_str_vec.clear();
                t0 = std::chrono::system_clock::now();
            }
        }

    }
    catch (const mqtt::exception& err) {
        std::cerr << err.what() << std::endl;
    }
}

void msg_callback(std::vector<std::string> pbuf_str_vec, std::mutex& io_mtx) {
    // https://mariadb.com/docs/server/connect/programming-languages/cpp/ 
    mtx.lock();
    for (int n = 0; n < pbuf_str_vec.size(); n++) {
        Cat kitty;
        kitty.ParseFromString(pbuf_str_vec[n]);
        std::cout << kitty.name() << ' ' << kitty.age() << std::endl;
    }
    mtx.unlock();
}

int main() {
    ThreadArgs cat_args;
    cat_args.batch_timeout = 10.0;
    cat_args.callback = msg_callback;
    cat_args.min_batch_size = 1;
    cat_args.max_batch_size = 2;
    cat_args.mqtt_topic = MQTT_DATA_TOPIC;

    std::thread cat_handler(thread_main, cat_args);
    cat_handler.join();
}