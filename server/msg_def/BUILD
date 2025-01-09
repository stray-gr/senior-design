# load("@rules_cc//cc:defs.bzl", "cc_library")
# load("@rules_proto//proto:defs.bzl", "proto_library")

# Conventions:
# 1. One proto_library rule per .proto file.
# 2. A file named foo.proto will be in a rule named foo_proto.
proto_library(
    name = "msg_proto",
    srcs = ["msg.proto"],
    deps = [
        # Well known protos should be included as deps in the
        # proto_library rules of the source files importing them.
        # A list of all @com_google_protobuf well known protos can
        # seen with:
        # `bazel query 'kind(proto_library, @com_google_protobuf//:all)'`
        # "@com_google_protobuf//:any_proto",
    ],
)

# Convention:
# A cc_proto_library that wraps a proto_library named foo_proto
# should be called foo_cc_proto.
cc_proto_library(
    name = "msg_cc_proto",
    visibility = ["//visibility:public"],
    deps = [":msg_proto"],
)
