# Same min CMake version as firmware project
cmake_minimum_required(VERSION 3.15)
project(server CXX)

# Ensure dependencies are installed
find_package(cpr REQUIRED)
find_package(libpqxx REQUIRED)
find_package(PahoMqttCpp REQUIRED)
find_package(protobuf CONFIG REQUIRED)

# Add library for protobuf message definitions 
add_subdirectory(msg_def)

# Create client
add_executable(client src/client.cc)
target_link_libraries(
    client 
    MSG_DEF 
    PahoMqttCpp::paho-mqttpp3-static
)
target_include_directories( 
    client PUBLIC 
    "${PROJECT_BINARY_DIR}" 
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/msg_def"
)

# Create clock
add_executable(clock src/clock.cc)
target_link_libraries(
    clock 
    PahoMqttCpp::paho-mqttpp3-static
)
target_include_directories( 
    clock PUBLIC 
    "${PROJECT_BINARY_DIR}" 
    "${PROJECT_SOURCE_DIR}/include"
)

# Create server
add_executable(server src/server.cc src/server_cb.cc)
target_link_libraries(
    server 
    cpr::cpr
    libpqxx::pqxx
    MSG_DEF
    PahoMqttCpp::paho-mqttpp3-static
    pthread
)
target_include_directories( 
    server PUBLIC 
    "${PROJECT_BINARY_DIR}" 
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/msg_def"
)
