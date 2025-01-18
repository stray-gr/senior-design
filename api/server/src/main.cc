#include <fstream>
#include <grpcpp/grpcpp.h>
#include <google/protobuf/empty.pb.h>
#include <iostream>
#include <sstream>

#include "api.grpc.pb.h"
#include "config.h"

class QueryImpl final : public api::Query::Service {
    grpc::Status GetResults(
        grpc::ServerContext *ctx, 
        const google::protobuf::Empty *in,
        grpc::ServerWriter<api::Point> *out
    ) override {
        api::Point p;

        for (int n = 0; n < 10; n++) {
            p.set_x(n);
            p.set_y(n * n);
            out->Write(p);
        }

        return grpc::Status::OK;
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

// Conan install > source > protoc > move sources
// update CMakeLists > cmake .. > CMake: Configure > CMake: Select a Configuration
int main() {
    std::string uri("0.0.0.0:3000");
    QueryImpl service;

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
