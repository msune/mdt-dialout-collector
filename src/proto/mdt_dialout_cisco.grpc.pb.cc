// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: mdt_dialout_cisco.proto

#include "mdt_dialout_cisco.pb.h"
#include "mdt_dialout_cisco.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace mdt_dialout {

static const char* gRPCMdtDialout_method_names[] = {
  "/mdt_dialout.gRPCMdtDialout/MdtDialout",
};

std::unique_ptr< gRPCMdtDialout::Stub> gRPCMdtDialout::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< gRPCMdtDialout::Stub> stub(new gRPCMdtDialout::Stub(channel, options));
  return stub;
}

gRPCMdtDialout::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_MdtDialout_(gRPCMdtDialout_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::BIDI_STREAMING, channel)
  {}

::grpc::ClientReaderWriter< ::mdt_dialout::MdtDialoutArgs, ::mdt_dialout::MdtDialoutArgs>* gRPCMdtDialout::Stub::MdtDialoutRaw(::grpc::ClientContext* context) {
  return ::grpc::internal::ClientReaderWriterFactory< ::mdt_dialout::MdtDialoutArgs, ::mdt_dialout::MdtDialoutArgs>::Create(channel_.get(), rpcmethod_MdtDialout_, context);
}

void gRPCMdtDialout::Stub::async::MdtDialout(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::mdt_dialout::MdtDialoutArgs,::mdt_dialout::MdtDialoutArgs>* reactor) {
  ::grpc::internal::ClientCallbackReaderWriterFactory< ::mdt_dialout::MdtDialoutArgs,::mdt_dialout::MdtDialoutArgs>::Create(stub_->channel_.get(), stub_->rpcmethod_MdtDialout_, context, reactor);
}

::grpc::ClientAsyncReaderWriter< ::mdt_dialout::MdtDialoutArgs, ::mdt_dialout::MdtDialoutArgs>* gRPCMdtDialout::Stub::AsyncMdtDialoutRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::mdt_dialout::MdtDialoutArgs, ::mdt_dialout::MdtDialoutArgs>::Create(channel_.get(), cq, rpcmethod_MdtDialout_, context, true, tag);
}

::grpc::ClientAsyncReaderWriter< ::mdt_dialout::MdtDialoutArgs, ::mdt_dialout::MdtDialoutArgs>* gRPCMdtDialout::Stub::PrepareAsyncMdtDialoutRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::mdt_dialout::MdtDialoutArgs, ::mdt_dialout::MdtDialoutArgs>::Create(channel_.get(), cq, rpcmethod_MdtDialout_, context, false, nullptr);
}

gRPCMdtDialout::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      gRPCMdtDialout_method_names[0],
      ::grpc::internal::RpcMethod::BIDI_STREAMING,
      new ::grpc::internal::BidiStreamingHandler< gRPCMdtDialout::Service, ::mdt_dialout::MdtDialoutArgs, ::mdt_dialout::MdtDialoutArgs>(
          [](gRPCMdtDialout::Service* service,
             ::grpc::ServerContext* ctx,
             ::grpc::ServerReaderWriter<::mdt_dialout::MdtDialoutArgs,
             ::mdt_dialout::MdtDialoutArgs>* stream) {
               return service->MdtDialout(ctx, stream);
             }, this)));
}

gRPCMdtDialout::Service::~Service() {
}

::grpc::Status gRPCMdtDialout::Service::MdtDialout(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::mdt_dialout::MdtDialoutArgs, ::mdt_dialout::MdtDialoutArgs>* stream) {
  (void) context;
  (void) stream;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace mdt_dialout

