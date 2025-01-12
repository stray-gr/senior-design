#ifndef SERVER_CALLBACKS
#define SERVER_CALLBACKS

#include <iostream>
#include <mutex>
#include <vector>

void data_callback(std::vector<std::string>& pbuf_str_vec, std::mutex& io_mtx, std::string tag);
void lwt_callback(std::vector<std::string>& pbuf_str_vec, std::mutex& io_mtx, std::string tag);

#endif