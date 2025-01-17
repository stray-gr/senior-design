cmake_minimum_required(VERSION 3.15)
project(server CXX)

# Ensure dependencies are installed
find_package(cpr REQUIRED)
find_package(libpqxx REQUIRED)
find_package(PahoMqttCpp REQUIRED)
find_package(protobuf REQUIRED)

# Create client
add_executable(client src/client.cc src/msg.pb.cc)
target_include_directories(client PRIVATE include)
target_link_libraries(client
    PahoMqttCpp::paho-mqttpp3-static
    protobuf::protobuf
)

# Create clock
add_executable(clock src/clock.cc)
target_include_directories(clock PRIVATE include)
target_link_libraries(clock PahoMqttCpp::paho-mqttpp3-static)

# Create server
add_executable(server src/msg.pb.cc src/server.cc src/server_cb.cc)
target_include_directories(server PRIVATE include)
target_link_libraries(server 
    cpr::cpr
    libpqxx::pqxx
    PahoMqttCpp::paho-mqttpp3-static
    protobuf::protobuf
    pthread
)
