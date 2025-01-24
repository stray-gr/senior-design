#ifndef LOCAL_SERVER
#define LOCAL_SERVER

#include <chrono>
#include <functional>
#include <map>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

namespace server {
    // server_utils.cc
    class Batch {
        private:
            // Read only members
            std::function<void (std::mutex*, std::vector<std::string>, std::string)> cb_;
            std::string tag_;
            size_t min_size_;
            size_t max_size_;
            double timeout_;

        public:
            // Read-Write members
            std::vector<std::string> msg_vec;
            std::chrono::time_point<std::chrono::system_clock> t0, t1;
            std::chrono::duration<double> dt;

            // Constructor prototype
            Batch(
                std::function<void (std::mutex*, std::vector<std::string>, std::string)> cb,
                std::string batch_tag,
                size_t min_batch_size,
                size_t max_batch_size,
                double batch_timeout
            );

            // Finished functions
            void run_callback(std::mutex *mtx) { cb_(mtx, msg_vec, tag_); }
            std::string tag() const { return tag_; }
            size_t min_size() const { return min_size_; }
            size_t max_size() const { return max_size_; }
            double  timeout() const { return timeout_; }
    };

    class EventLoop {
        private:
            // Maps MQTT subscription to batch configs
            std::map<std::string, Batch> batches_;

        public:
            // Constructor prototype
            EventLoop(std::map<std::string, Batch> batches);
            void start();
    };

    class ThreadPool {
        private:
            int thread_count_;
            std::queue<Batch> task_queue_;
            std::mutex task_queue_mtx_;
            void thread_main();

        public:
            ThreadPool(size_t thread_count);
            void add_task(Batch task);
            void start();
    };

    // server_callbacks.cc
    namespace callbacks {
        // DB connection pool shared mutex (static)
        // DB connection pool size (static)
        // DB connection pool max size (config.h)
        void sensor_callback(std::mutex *io_mtx, std::vector<std::string> pb_vec, std::string tag);
        void lwt_callback(std::mutex *io_mtx, std::vector<std::string> pb_vec, std::string tag);
    }
}

#endif
