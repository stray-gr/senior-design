#include <fstream>
#include <google/protobuf/empty.pb.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/security/server_credentials.h>
#include <iostream>
#include <mutex>

#include "api.grpc.pb.h"
#include "config.h"

class QueryImpl final : public api::Query::CallbackService {
    private:
        std::string conn_;
        std::mutex *mtx_;

    public:
        explicit QueryImpl(std::string conn, std::mutex *mtx) {
            this->conn_ = conn;
            this->mtx_ = mtx;
        }

        grpc::ServerWriteReactor<api::Point> *GetResults(
            grpc::CallbackServerContext *ctx,
            const google::protobuf::Empty *req
        ) override {
            class Getter : public grpc::ServerWriteReactor<api::Point> {
                private:
                    const std::string *conn_ref_;
                    std::mutex *mtx_ref_;
                    int i_;
                    api::Point p;

                    void NextWrite() {
                        // Use transaction iterator (not transaction.end())
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
                    // Getter(
                    //     const google::protobuf::Empty *req, 
                    //     const std::string *conn, 
                    //     std::mutex *mtx
                    // ) : conn_ref_(conn), mtx_ref_(mtx), i_(0) {
                    //     NextWrite();
                    // }
                    Getter(
                        const google::protobuf::Empty *req, 
                        const std::string *conn, 
                        std::mutex *mtx
                    ) {
                        this->conn_ref_ = conn;
                        this->mtx_ref_ = mtx;
                        this->i_ = 0;

                        // Create transaction iterator

                        NextWrite();
                    }

                    void OnWriteDone(bool ok) override {
                        if (!ok) {
                            Finish(grpc::Status(grpc::StatusCode::UNKNOWN, "Uncaught Exception"));
                        }

                        NextWrite();
                    }

                    void OnDone() override {
                        // Complete stream and commit transaction
                        delete this;
                    }

                    void OnCancel() override {
                        // Complete stream and rollback transaction
                    }
            };

            return new Getter(req, &conn_, mtx_);
        }
};

std::string load_cert(std::string path) {
    std::ifstream cert(path);
    if (!cert.is_open()) {
        std::cout << "Failed to open "  << path << std::endl;
        abort();
    }

    std::stringstream buf;
    buf << cert.rdbuf();
    return buf.str();
}

// CMake: Configure
int main() {
    std::string uri("0.0.0.0:3000");

    std::mutex conn_mtx;
    QueryImpl service("db string", &conn_mtx);

    grpc::SslServerCredentialsOptions::PemKeyCertPair key_cert_pair = {
        load_cert(API_KEY),
        load_cert(API_CRT)
    };
    grpc::SslServerCredentialsOptions ssl_options;
    ssl_options.pem_root_certs = load_cert(CA_CRT);
    ssl_options.pem_key_cert_pairs.emplace_back(key_cert_pair);
    ssl_options.client_certificate_request = GRPC_SSL_REQUEST_AND_REQUIRE_CLIENT_CERTIFICATE_AND_VERIFY;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(uri, grpc::SslServerCredentials(ssl_options));
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Running on " << uri << std::endl;
    server->Wait();
}
