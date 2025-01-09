# NOTE
- Run `protoc --cpp_out=. ./msg.proto` to create a header file that can be included in other modules to prevent linting errors
- The actual protobuf object file is built by bazel. This prevents build errors with the header file