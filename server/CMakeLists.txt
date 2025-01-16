# Same min CMake version as firmware project
cmake_minimum_required(VERSION 3.15)
project(server CXX)

# Ensure dependencies are installed
find_package(cpr REQUIRED)
find_package(libpqxx REQUIRED)
find_package(PahoMqttCpp REQUIRED)
find_package(protobuf CONFIG REQUIRED)

# Add library for protobuf message definitions 
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS msg.proto)

# Create client
add_executable(client src/client.cc ${PROTO_SRCS})
target_include_directories(client PUBLIC include)
target_include_directories(client PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)
target_link_libraries(client PUBLIC
    PahoMqttCpp::paho-mqttpp3-static
    protobuf::libprotobuf
)

# Create clock
add_executable(clock src/clock.cc)
target_include_directories(clock PUBLIC include)
target_include_directories(clock PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)
target_link_libraries(clock PUBLIC
    PahoMqttCpp::paho-mqttpp3-static
)

# Create server
add_executable(server src/server.cc src/server_cb.cc ${PROTO_SRCS})
target_include_directories(server PUBLIC include)
target_include_directories(server PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)
target_link_libraries(server PUBLIC
    cpr::cpr
    libpqxx::pqxx
    PahoMqttCpp::paho-mqttpp3-static
    protobuf::libprotobuf
    pthread
)
