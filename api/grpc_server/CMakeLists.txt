cmake_minimum_required(VERSION 3.15)
project(mypkg CXX)

# Ensure dependencies are installed
find_package(gRPC REQUIRED)
find_package(libpqxx REQUIRED)

# Create client
add_executable(main 
    src/api.grpc.pb.cc 
    src/api.pb.cc 
    src/main.cc
    src/service_callbacks.cc
    src/service_utils.cc
)
target_include_directories(main PRIVATE include)
target_link_libraries(main grpc::grpc libpqxx::pqxx)
