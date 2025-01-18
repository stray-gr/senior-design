# Set Up
- Build protobuf definitions:
    ```bash
    protoc --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./api.proto
    protoc --cpp_out=. ./api.proto
    ```

# Useful links
- https://docs.conan.io/2.11/tutorial/consuming_packages/use_tools_as_conan_packages.html
- https://docs.conan.io/2.11/tutorial/consuming_packages/build_simple_cmake_project.html