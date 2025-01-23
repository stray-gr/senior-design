# Set Up
- Build protobuf definitions:
    ```bash
    conan install . --output-folder=build --build=missing
    source build/conanbuild.sh
    protoc -I../ --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ../api.proto
    protoc -I../ --cpp_out=. ../api.proto
    cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
    cmake --build . --config Release
    ```

# Useful links
- https://docs.conan.io/2.11/tutorial/consuming_packages/use_tools_as_conan_packages.html
- https://docs.conan.io/2.11/tutorial/consuming_packages/build_simple_cmake_project.html