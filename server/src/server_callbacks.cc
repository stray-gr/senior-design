#include <cpr/cpr.h>
#include <pqxx/pqxx>

#include "config.h"
#include "msg.pb.h"
#include "server.h"

/* Makeshift Counting Semaphore */
static std::mutex DB_CONN_POOL_MTX;
static int DB_CONN_POOL_SIZE = MAX_DB_CONN_POOL_SIZE;
static void reserve_connection_slot() {
    while (true) {
        DB_CONN_POOL_MTX.lock();
        if (DB_CONN_POOL_SIZE > 0) {
            DB_CONN_POOL_SIZE -= 1;
            DB_CONN_POOL_MTX.unlock();
            return;
        }
        else {
            DB_CONN_POOL_MTX.unlock();
        }
    }
}
static void release_connection_slot() {
    DB_CONN_POOL_MTX.lock();
    DB_CONN_POOL_SIZE += 1;
    DB_CONN_POOL_MTX.unlock();
}

void server::callbacks::sensor_callback(std::mutex *io_mtx, std::vector<std::string> pb_vec, std::string tag) {
    char *DB_CONN_STR = std::getenv("DB_CONN_STR");
    char *FACILITY_ID_STR = std::getenv("FACILITY_ID");
    if ((DB_CONN_STR == nullptr) || (FACILITY_ID_STR == nullptr)) {
        io_mtx->lock();
        std::cout << tag << " | Environment variables missing... exiting" << std::endl;
        io_mtx->unlock();
        return;
    }

    int FACILITY_ID = std::atoi(FACILITY_ID_STR);
    if (FACILITY_ID == 0) {
        io_mtx->lock();
        std::cout << tag << " | Could not convert Facility ID to int... exiting" << std::endl;
        io_mtx->unlock();
        return;
    }

    /* BEGIN DB CONNECTION */ 
    reserve_connection_slot();
    pqxx::connection cx{DB_CONN_STR};
    pqxx::work tx{cx};
    auto stream = pqxx::stream_to::table(
        tx, 
        std::initializer_list<std::string_view>{"data", "sensor"}, 
        std::initializer_list<std::string_view>{"facility_id", "device", "temp", "rh", "epoch"}
    );

    msg::Sensor sensor_data;
    for (size_t i = 0; i < pb_vec.size(); i++) {
        sensor_data.ParseFromString(pb_vec[i]);
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
    release_connection_slot(); 
    /* END DB CONNECTION */ 

    io_mtx->lock();
    std::cout << tag <<" | Batch processed" << std::endl;
    io_mtx->unlock();
}

void server::callbacks::lwt_callback(std::mutex *io_mtx, std::vector<std::string> pb_vec, std::string tag) {
    char *BOT_ID = std::getenv("BOT_ID");
    if (BOT_ID == nullptr) {
        io_mtx->lock();
        std::cout << tag << " | Environment variable missing... exiting" << std::endl;
        io_mtx->unlock();
        return;
    }

    std::string device_str{"The following device(s) have shutdown: "};
    for (size_t i = 0; i < pb_vec.size(); i++) {
        msg::LWT lwt_msg;
        lwt_msg.ParseFromString(pb_vec[i]);
        device_str.append("\n> " + lwt_msg.device());
    }

    cpr::Response resp = cpr::Post(
        cpr::Url{"https://api.groupme.com/v3/bots/post"},
        cpr::Parameters{{"text", device_str}, {"bot_id", BOT_ID}}
    );

    io_mtx->lock();
    if (!resp.error.message.empty()) {
        std::cout << tag << " | ERROR: " << resp.error.message << std::endl;
    }
    else {
        std::cout << tag << " | Outage Size " << pb_vec.size() << " - HTTP Status Code " << resp.status_code << std::endl;
    }
    io_mtx->unlock();
}