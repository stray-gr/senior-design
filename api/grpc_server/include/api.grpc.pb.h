// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: api.proto
#ifndef GRPC_api_2eproto__INCLUDED
#define GRPC_api_2eproto__INCLUDED

#include "api.pb.h"

#include <functional>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/proto_utils.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/stub_options.h>
#include <grpcpp/support/sync_stream.h>

namespace api {

class Query final {
 public:
  static constexpr char const* service_full_name() {
    return "api.Query";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    std::unique_ptr< ::grpc::ClientReaderInterface< ::api::SensorRows>> GetSensorRows(::grpc::ClientContext* context, const ::google::protobuf::Empty& request) {
      return std::unique_ptr< ::grpc::ClientReaderInterface< ::api::SensorRows>>(GetSensorRowsRaw(context, request));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::api::SensorRows>> AsyncGetSensorRows(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::api::SensorRows>>(AsyncGetSensorRowsRaw(context, request, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::api::SensorRows>> PrepareAsyncGetSensorRows(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderInterface< ::api::SensorRows>>(PrepareAsyncGetSensorRowsRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void GetSensorRows(::grpc::ClientContext* context, const ::google::protobuf::Empty* request, ::grpc::ClientReadReactor< ::api::SensorRows>* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientReaderInterface< ::api::SensorRows>* GetSensorRowsRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request) = 0;
    virtual ::grpc::ClientAsyncReaderInterface< ::api::SensorRows>* AsyncGetSensorRowsRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq, void* tag) = 0;
    virtual ::grpc::ClientAsyncReaderInterface< ::api::SensorRows>* PrepareAsyncGetSensorRowsRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    std::unique_ptr< ::grpc::ClientReader< ::api::SensorRows>> GetSensorRows(::grpc::ClientContext* context, const ::google::protobuf::Empty& request) {
      return std::unique_ptr< ::grpc::ClientReader< ::api::SensorRows>>(GetSensorRowsRaw(context, request));
    }
    std::unique_ptr< ::grpc::ClientAsyncReader< ::api::SensorRows>> AsyncGetSensorRows(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReader< ::api::SensorRows>>(AsyncGetSensorRowsRaw(context, request, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReader< ::api::SensorRows>> PrepareAsyncGetSensorRows(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReader< ::api::SensorRows>>(PrepareAsyncGetSensorRowsRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void GetSensorRows(::grpc::ClientContext* context, const ::google::protobuf::Empty* request, ::grpc::ClientReadReactor< ::api::SensorRows>* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientReader< ::api::SensorRows>* GetSensorRowsRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request) override;
    ::grpc::ClientAsyncReader< ::api::SensorRows>* AsyncGetSensorRowsRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq, void* tag) override;
    ::grpc::ClientAsyncReader< ::api::SensorRows>* PrepareAsyncGetSensorRowsRaw(::grpc::ClientContext* context, const ::google::protobuf::Empty& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_GetSensorRows_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status GetSensorRows(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::grpc::ServerWriter< ::api::SensorRows>* writer);
  };
  template <class BaseClass>
  class WithAsyncMethod_GetSensorRows : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_GetSensorRows() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_GetSensorRows() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetSensorRows(::grpc::ServerContext* /*context*/, const ::google::protobuf::Empty* /*request*/, ::grpc::ServerWriter< ::api::SensorRows>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetSensorRows(::grpc::ServerContext* context, ::google::protobuf::Empty* request, ::grpc::ServerAsyncWriter< ::api::SensorRows>* writer, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncServerStreaming(0, context, request, writer, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_GetSensorRows<Service > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_GetSensorRows : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_GetSensorRows() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackServerStreamingHandler< ::google::protobuf::Empty, ::api::SensorRows>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::google::protobuf::Empty* request) { return this->GetSensorRows(context, request); }));
    }
    ~WithCallbackMethod_GetSensorRows() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetSensorRows(::grpc::ServerContext* /*context*/, const ::google::protobuf::Empty* /*request*/, ::grpc::ServerWriter< ::api::SensorRows>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerWriteReactor< ::api::SensorRows>* GetSensorRows(
      ::grpc::CallbackServerContext* /*context*/, const ::google::protobuf::Empty* /*request*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_GetSensorRows<Service > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_GetSensorRows : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_GetSensorRows() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_GetSensorRows() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetSensorRows(::grpc::ServerContext* /*context*/, const ::google::protobuf::Empty* /*request*/, ::grpc::ServerWriter< ::api::SensorRows>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_GetSensorRows : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_GetSensorRows() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_GetSensorRows() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetSensorRows(::grpc::ServerContext* /*context*/, const ::google::protobuf::Empty* /*request*/, ::grpc::ServerWriter< ::api::SensorRows>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetSensorRows(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncWriter< ::grpc::ByteBuffer>* writer, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncServerStreaming(0, context, request, writer, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_GetSensorRows : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_GetSensorRows() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackServerStreamingHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const::grpc::ByteBuffer* request) { return this->GetSensorRows(context, request); }));
    }
    ~WithRawCallbackMethod_GetSensorRows() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetSensorRows(::grpc::ServerContext* /*context*/, const ::google::protobuf::Empty* /*request*/, ::grpc::ServerWriter< ::api::SensorRows>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerWriteReactor< ::grpc::ByteBuffer>* GetSensorRows(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/)  { return nullptr; }
  };
  typedef Service StreamedUnaryService;
  template <class BaseClass>
  class WithSplitStreamingMethod_GetSensorRows : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithSplitStreamingMethod_GetSensorRows() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::SplitServerStreamingHandler<
          ::google::protobuf::Empty, ::api::SensorRows>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerSplitStreamer<
                     ::google::protobuf::Empty, ::api::SensorRows>* streamer) {
                       return this->StreamedGetSensorRows(context,
                         streamer);
                  }));
    }
    ~WithSplitStreamingMethod_GetSensorRows() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status GetSensorRows(::grpc::ServerContext* /*context*/, const ::google::protobuf::Empty* /*request*/, ::grpc::ServerWriter< ::api::SensorRows>* /*writer*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with split streamed
    virtual ::grpc::Status StreamedGetSensorRows(::grpc::ServerContext* context, ::grpc::ServerSplitStreamer< ::google::protobuf::Empty,::api::SensorRows>* server_split_streamer) = 0;
  };
  typedef WithSplitStreamingMethod_GetSensorRows<Service > SplitStreamedService;
  typedef WithSplitStreamingMethod_GetSensorRows<Service > StreamedService;
};

}  // namespace api


#endif  // GRPC_api_2eproto__INCLUDED
