# Create library for protobuf message definitions
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS msg.proto)
add_library(MSG_DEF ${PROTO_SRCS})
target_link_libraries(MSG_DEF protobuf::protobuf)