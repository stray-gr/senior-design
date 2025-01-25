#include <fstream>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server_builder.h>
#include <iostream>
#include <sstream>

#include "service.h"

static std::string load_cert(std::string path) {
    std::ifstream cert(path);
    if (!cert.is_open()) {
        std::cout << "Failed to open "  << path << std::endl;
        abort();
    }

    std::stringstream buf;
    buf << cert.rdbuf();
    return buf.str();
}

void service::run(std::string uri = "0.0.0.0:3000") {
    char *DB_CONN_STR = std::getenv("DB_CONN_STR");
    char *CA_CRT = std::getenv("CA_CRT");
    char *SERVICE_CRT = std::getenv("SERVICE_CRT");
    char *SERVICE_KEY = std::getenv("SERVICE_KEY");

    if (
        (DB_CONN_STR == nullptr) || 
        (CA_CRT == nullptr) ||
        (SERVICE_CRT == nullptr) ||
        (SERVICE_KEY == nullptr)
    ) {
        std::cout << " SERVICE | Environment variables missing... exiting" << std::endl;
        return;
    }

    service::QueryImpl grpc_server(DB_CONN_STR);
    grpc::SslServerCredentialsOptions::PemKeyCertPair key_cert_pair = {
        load_cert(SERVICE_KEY),
        load_cert(SERVICE_CRT)
    };

    grpc::SslServerCredentialsOptions ssl_options;
    ssl_options.pem_root_certs = load_cert(CA_CRT);
    ssl_options.pem_key_cert_pairs.emplace_back(key_cert_pair);
    ssl_options.client_certificate_request = GRPC_SSL_REQUEST_AND_REQUIRE_CLIENT_CERTIFICATE_AND_VERIFY;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(uri, grpc::SslServerCredentials(ssl_options));
    builder.RegisterService(&grpc_server);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "SERVICE | Running on " << uri << std::endl;
    server->Wait();
}