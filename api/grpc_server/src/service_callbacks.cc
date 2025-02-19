#include <google/protobuf/empty.pb.h>
#include <iostream>
#include <list>
#include <mutex>
#include <pqxx/pqxx>
#include <stdexcept>

#include "config.h"
#include "service.h"

static std::mutex IO_MTX;

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

service::QueryImpl::QueryImpl(char *db_conn_str) {
    if (db_conn_str == nullptr) {
        throw std::invalid_argument("DB Connection C-String cannot be a nullptr");
    }

    this->db_conn_str_ = db_conn_str;
}

grpc::ServerWriteReactor<api::SensorRows> *service::QueryImpl::GetSensorRows(
    grpc::CallbackServerContext *ctx,
    const google::protobuf::Empty *req
) {
    class ResultStream : public grpc::ServerWriteReactor<api::SensorRows> {
        private:
            std::list<api::SensorRows> rows_;
            api::SensorRows r_;

            void NextWrite() {
                while (!rows_.empty()) {
                    r_ = rows_.front();
                    rows_.pop_front();

                    StartWrite(&r_);
                    return;
                }

                Finish(grpc::Status::OK);
            }
        
        public:
            ResultStream(std::list<api::SensorRows> rows) {
                this->rows_ = rows;
                NextWrite();
            }

            void OnWriteDone(bool ok) override {
                if (!ok) {
                    Finish(grpc::Status(grpc::StatusCode::UNKNOWN, "Uncaught Exception"));
                }

                NextWrite();
            }

            void OnDone() override {
                delete this;
            }

            void OnCancel() override {}
    };

    try {
        IO_MTX.lock();
        std::cout << "SERVICE | GetSensorRows - received" << std::endl;
        IO_MTX.unlock();

        reserve_connection_slot();
        pqxx::connection cx = pqxx::connection(db_conn_str_);
        pqxx::work tx = pqxx::work(cx);

        api::SensorRows row;
        std::list<api::SensorRows> row_list;
        for (
            auto [entry_id, facility_id, device, temp, rh, epoch] : 
            tx.stream<int, int, std::string, int, float, time_t>("SELECT * FROM data.sensor")
        ) {
            row.set_entry_id(entry_id);
            row.set_facility_id(facility_id);
            row.set_device(device);
            row.set_temp(temp);
            row.set_rh(rh);
            row.set_epoch(epoch);

            row_list.push_back(row);
        }

        cx.close();
        release_connection_slot();
        return new ResultStream(std::move(row_list));
    } 
    catch (std::exception& err) {
        IO_MTX.lock();
        std::cout << "SERVICE | GetSensorRows - " << err.what() << std::endl;
        IO_MTX.unlock();

        release_connection_slot();
        throw err;
    }

}
