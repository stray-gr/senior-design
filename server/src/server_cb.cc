#include <cpr/cpr.h>
#include <cstdlib>
#include <pqxx/pqxx>
#include "server_cb.h"
#include "msg.pb.h"

void data_callback(std::vector<std::string>& pbuf_str_vec, std::mutex& io_mtx, std::string tag) {
    char *DB_CONN_STR = std::getenv("DB_CONN_STR");
    char *FACILITY_ID_STR = std::getenv("FACILITY_ID");
    if ((DB_CONN_STR == nullptr) || (FACILITY_ID_STR == nullptr)) {
        io_mtx.lock();
        std::cout << tag << " | Environment variables missing... exiting" << std::endl;
        io_mtx.unlock();
        return;
    }

    int FACILITY_ID = std::atoi(FACILITY_ID_STR);
    if (FACILITY_ID == 0) {
        io_mtx.lock();
        std::cout << tag << " | Could not convert Facility ID to int... exiting" << std::endl;
        io_mtx.unlock();
        return;
    }

    Data sensor_data;
    pqxx::connection cx{DB_CONN_STR};
    pqxx::work tx{cx};
    auto stream = pqxx::stream_to::table(
        tx, 
        std::initializer_list<std::string_view>{"data", "sensor"}, 
        std::initializer_list<std::string_view>{"facility_id", "device", "temp", "rh", "epoch"}
    );

    for (size_t n = 0; n < pbuf_str_vec.size(); n++) {
        sensor_data.ParseFromString(pbuf_str_vec[n]);
        stream.write_values(
            FACILITY_ID,
            sensor_data.device(),
            sensor_data.temp(),
            sensor_data.rh(),
            sensor_data.epoch()
        );
    }
    stream.complete();
    tx.commit();

    io_mtx.lock();
    std::cout << tag <<" | Batch processed" << std::endl;
    io_mtx.unlock();
}

void lwt_callback(std::vector<std::string>& pbuf_str_vec, std::mutex& io_mtx, std::string tag) {
    char *BOT_ID = std::getenv("BOT_ID");
    if (BOT_ID == nullptr) {
        io_mtx.lock();
        std::cout << tag << " | Environment variable missing... exiting" << std::endl;
        io_mtx.unlock();
        return;
    }

    std::string device_str{"The following device(s) have shutdown: "};
    for (size_t n = 0; n < pbuf_str_vec.size(); n++) {
        LWT msg;
        msg.ParseFromString(pbuf_str_vec[n]);
        device_str.append("\n> " + msg.device());
    }

    cpr::Response resp = cpr::Post(
        cpr::Url{"https://api.groupme.com/v3/bots/post"},
        cpr::Parameters{{"text", device_str}, {"bot_id", BOT_ID}}
    );

    io_mtx.lock();
    if (!resp.error.message.empty()) {
        std::cout << tag << " | ERROR: " << resp.error.message << std::endl;
    }
    else {
        std::cout << tag << " | Outage Size " << pbuf_str_vec.size() << " - HTTP Status Code " << resp.status_code << std::endl;
    }
    io_mtx.unlock();
}