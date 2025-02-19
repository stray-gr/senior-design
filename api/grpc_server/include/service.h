#ifndef GRPC_SERVER
#define GRPC_SERVER

#include <string>
#include "api.grpc.pb.h"

namespace service {
    // service_callbacks.cc
    class QueryImpl final : public api::Query::CallbackService {
        private:
            char *db_conn_str_;

        public:
            explicit QueryImpl(char *db_conn_str);
            grpc::ServerWriteReactor<api::SensorRows> *GetSensorRows(
                grpc::CallbackServerContext *ctx,
                const google::protobuf::Empty *req
            ) override;

    };

    // service_utils.cc
    void run(std::string uri = "0.0.0.0:3000");
}

#endif