cmake_minimum_required(VERSION 3.15)
project(server CXX)

# Ensure dependencies are installed
find_package(gRPC REQUIRED)

# Create client
add_executable(main src/api.grpc.pb.cc src/api.pb.cc src/main.cc)
target_include_directories(main PRIVATE include)
target_link_libraries(main grpc::grpc)
