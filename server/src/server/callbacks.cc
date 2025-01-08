#include "callbacks.h"
#include "../msg.pb.h"

void data_callback(std::vector<std::string>& pbuf_str_vec, std::mutex& io_mtx, std::string tag) {
    // https://mariadb.com/docs/server/connect/programming-languages/cpp/ 
    io_mtx.lock();
    for (size_t n = 0; n < pbuf_str_vec.size(); n++) {
        Cat kitty;
        kitty.ParseFromString(pbuf_str_vec[n]);
        std::cout << tag << " | " << kitty.name() << ' ' << kitty.age() << std::endl;
    }
    io_mtx.unlock();
}

void lwt_callback(std::vector<std::string>& pbuf_str_vec, std::mutex& io_mtx, std::string tag) {
    // https://curl.se/libcurl/
    io_mtx.lock();
    for (size_t n = 0; n < pbuf_str_vec.size(); n++) {
        std::cout << tag << " | " << pbuf_str_vec[n] << std::endl;
    }
    io_mtx.unlock();
}