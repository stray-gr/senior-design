#include <cstdlib>
#include <pqxx/pqxx>
#include "callbacks.h"
#include "msg.pb.h"

void data_callback(std::vector<std::string>& pbuf_str_vec, std::mutex& io_mtx, std::string tag) {
    char *DB_CONN_STR = std::getenv("DB_CONN_STR");
    char *DB_TABLE = std::getenv("DB_TABLE");
    if ((DB_CONN_STR == nullptr) || (DB_TABLE == nullptr)) {
        io_mtx.lock();
        std::cout << tag << " | Environment variables missing... exiting" << std::endl;
        io_mtx.unlock();
        return;
    }

    Cat kitty;
    pqxx::connection cx{DB_CONN_STR};
    pqxx::work tx{cx};
    auto stream = pqxx::stream_to::table(
        tx, 
        std::initializer_list<std::string_view>{"data", DB_TABLE}, 
        std::initializer_list<std::string_view>{"device", "temp", "rh", "epoch"}
    );

    for (size_t n = 0; n < pbuf_str_vec.size(); n++) {
        kitty.ParseFromString(pbuf_str_vec[n]);
        stream.write_values(kitty.name(), kitty.age());
    }
    stream.complete();
    tx.commit();

    io_mtx.lock();
    std::cout << tag <<" | Batch processed" << std::endl;
    io_mtx.unlock();
}

void lwt_callback(std::vector<std::string>& pbuf_str_vec, std::mutex& io_mtx, std::string tag) {
    // Discord chat bot
    io_mtx.lock();
    for (size_t n = 0; n < pbuf_str_vec.size(); n++) {
        std::cout << tag << " | " << pbuf_str_vec[n] << std::endl;
    }
    io_mtx.unlock();
}