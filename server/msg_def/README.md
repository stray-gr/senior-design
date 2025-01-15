# NOTE
- Run `protoc --cpp_out=./msg_def ./msg.proto` to create a header file that can be included in other modules to prevent linting errors
- The actual protobuf object file is built by CMake. This prevents build errors with the header file