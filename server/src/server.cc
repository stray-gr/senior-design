#include <iostream>
#include <map>

#include "config.h"
#include "server.h"

int main() {
    server::Batch sensor_data(server::callbacks::sensor_callback, "DATA  ", 1, 2, 10.0);
    server::Batch lwt(server::callbacks::lwt_callback, "LWT   ", 1, 2, 10.0);

    std::map<std::string, server::Batch> batches {
        {MQTT_DATA_TOPIC, sensor_data},
        {MQTT_LWT_TOPIC, lwt}
    };

    server::EventLoop local_server(batches);
    local_server.start();
}