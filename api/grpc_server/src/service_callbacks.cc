#include <google/protobuf/empty.pb.h>
#include <iostream>
#include <memory>
#include <mutex>
#include <pqxx/pqxx>

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

explicit service::QueryImpl::QueryImpl(char *db_conn_str) {
    if (db_conn_str == nullptr) {
        // TODO: throw
    }

    this->db_conn_str_ = db_conn_str;
}

grpc::ServerWriteReactor<api::Point> *service::QueryImpl::GetResults(
    grpc::CallbackServerContext *ctx,
    const google::protobuf::Empty *req
) {
    class ResultStream : public grpc::ServerWriteReactor<api::Point> {
        private:
            std::unique_ptr<pqxx::connection> cx_;
            std::unique_ptr<pqxx::work> tx_;
            std::unique_ptr<pqxx::stream_from> stream_;
            bool cancelled_;
            int i_;
            api::Point p;

            void NextWrite() {
                // TODO: Use transaction iterator (not transaction.end())
                // TODO: Update grpc protobuf definitions
                if (i_ < 10) {
                    p.set_x(i_);
                    p.set_y(i_ * i_);

                    StartWrite(&p);

                    i_++;
                    return;
                }

                Finish(grpc::Status::OK);
            }
        
        public:
            ResultStream(char *db_conn_str) {
                this->cancelled_ = false;
                this->i_ = 0;

                // Create stream
                reserve_connection_slot();
                this->cx_ = std::make_unique<pqxx::connection>(pqxx::connection{db_conn_str});
                this->tx_ = std::make_unique<pqxx::work>(pqxx::work{*this->cx_});
                this->stream_ = std::make_unique<pqxx::stream_from>(
                    pqxx::stream_from::query(*this->tx_, "SELECT * FROM data.sensor")
                );

                NextWrite();
            }

            void OnWriteDone(bool ok) override {
                if (!ok) {
                    Finish(grpc::Status(grpc::StatusCode::UNKNOWN, "Uncaught Exception"));
                }

                NextWrite();
            }

            void OnDone() override {
                // Complete stream, end transaction, and release connection slot
                stream_->complete();
                if (cancelled_) {
                    tx_->abort();
                }
                else {
                    tx_->commit();
                }
                release_connection_slot();
                delete this;
            }

            void OnCancel() override {
                cancelled_ = true;
            }
    };

    return new ResultStream(db_conn_str_);
}
