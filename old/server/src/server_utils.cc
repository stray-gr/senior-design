#include <mqtt/client.h>

#include "config.h"
#include "server.h"

static std::mutex IO_MTX;

server::Batch::Batch(
    std::function<void (std::mutex*, std::vector<std::string>, std::string)> cb, 
    std::string batch_tag, 
    size_t min_batch_size, 
    size_t max_batch_size, 
    double batch_timeout
) {
    // Update read-only members
    this->cb_  = cb;
    this->tag_ = batch_tag;
    this->min_size_ = min_batch_size;
    this->max_size_ = max_batch_size;
    this->timeout_  = batch_timeout;

    // Resize message vector to minimize reallocations
    this->msg_vec.reserve(max_batch_size + 1);
}

server::EventLoop::EventLoop(std::map<std::string, Batch> batches) {
    this->batches_ = batches;
}

void server::EventLoop::start() {
    char *MQTT_PASS = std::getenv("MQTT_SERVER_PASS");
    char *MSG_BROKER_URI = std::getenv("VIRTUAL_BROKER_URI");
    if ((MQTT_PASS == nullptr) || (MSG_BROKER_URI == nullptr)) {
        IO_MTX.lock();
        std::cout << "SERVER | Environment variables missing... exiting" << std::endl;
        IO_MTX.unlock();
        return;
    }

    mqtt::client user(MSG_BROKER_URI, MQTT_SERVER_USER, mqtt::create_options(5));
    auto conn_opts = mqtt::connect_options_builder()
        .automatic_reconnect(std::chrono::seconds(1), std::chrono::seconds(15)) // 2**0 + ... + 2**3 = 15
        .clean_start()
        .mqtt_version(5)
        .user_name(MQTT_SERVER_USER)
        .password(MQTT_PASS)
        .finalize();

    try {
        IO_MTX.lock();
        mqtt::connect_response resp = user.connect(conn_opts);
        std::cout << "SERVER | Connected to " << MSG_BROKER_URI << std::endl;
        IO_MTX.unlock();

        if (!resp.is_session_present()) {
            mqtt::subscribe_options sub_opts;
            mqtt::properties props;
            
            for (auto it = batches_.begin(); it != batches_.end(); it++) {
                // it->first is the mqtt topic name
                user.subscribe(it->first, 1, sub_opts, props);
                IO_MTX.lock();
                std::cout << "SERVER | Subscribed to " << it->first << std::endl;
                IO_MTX.unlock();
            }
        }

        for (auto it = batches_.begin(); it != batches_.end(); it++) {
            // it->second is the batch 
            it->second.t0 = std::chrono::system_clock::now();
        }

        ThreadPool worker_queue(4);
        worker_queue.start();

        while(true) { 
            mqtt::const_message_ptr msg;

            if (user.try_consume_message(&msg)) {
                // Try consuming a message
                std::string topic{msg->get_topic()};

                if (batches_.count(topic) != 1) {
                    // Message topic not found
                    IO_MTX.lock();
                    std::cout << "SERVER | Skipping message from topic: " << topic << std::endl;
                    IO_MTX.unlock();
                    continue;
                }

                // Add message to corresponding batch
                std::string pb_str{msg->get_payload_str()};
                batches_.at(topic).msg_vec.push_back(pb_str);
            }

            for (auto it = batches_.begin(); it != batches_.end(); it++) {
                // Load copy of batch 
                Batch batch = it->second;

                // If batch message queue is empty, start new timeout (reset t0)
                if (batch.msg_vec.empty()) {
                    batch.t0 = std::chrono::system_clock::now();
                }

                // Get current timeout (dt)
                batch.t1 = std::chrono::system_clock::now();
                batch.dt = batch.t1 - batch.t0;

                if (
                    (batch.dt.count() >= batch.timeout() && batch.msg_vec.size() >= batch.min_size()) ||
                    (batch.msg_vec.size() >= batch.max_size())
                ) {
                    // Add batch to worker queue if conditions are met
                    IO_MTX.lock();
                    std::cout << "SERVER | Adding task to thread" << std::endl;
                    IO_MTX.unlock();

                    worker_queue.add_task(batch);
                    batch.msg_vec.clear();
                    batch.t0 = std::chrono::system_clock::now();
                }

                // Update batch entry
                it->second = batch;
            }
        }
    }
    catch (const mqtt::exception& err) {
        std::cerr << "SERVER | " << err.what() << std::endl;
    }
}

static void thread_main(std::mutex *task_queue_mtx, std::list<server::Batch> *task_queue) {
    // Grab and run task
    while (true) {
        task_queue_mtx->lock();
        if (!task_queue->empty()) {
            server::Batch task = task_queue->front();
            task_queue->pop_front();
            task_queue_mtx->unlock();
            task.run_callback(&IO_MTX);
        }
        else {
            task_queue_mtx->unlock();
        }
    }
}

server::ThreadPool::ThreadPool(size_t thread_count = std::thread::hardware_concurrency()) {
    this->thread_count_ = thread_count;
}

void server::ThreadPool::add_task(Batch task) {
    task_queue_mtx_.lock();
    task_queue_.push_back(task);
    task_queue_mtx_.unlock();
}

void server::ThreadPool::start() {
    // Spawn threads
    for (size_t i = 0; i < thread_count_; i++) {
        std::thread(thread_main, &task_queue_mtx_, &task_queue_).detach();
    }
}
