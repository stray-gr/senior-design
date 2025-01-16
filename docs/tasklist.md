# Proof-of-Concepts
## 1. Input Subsystem
### 1a. Firmware
- Install the following:
	1. Mosquitto MQTT Broker
	1. PlatformIO IDE and vscode-proto3 plugins for VS Code
	2. Protobuf compiler and the protobuf-c plugin
	3. The MQTTX CLI Tool
	4. Wokwi CLI
- Set up message broker TLS and user roles
- Create a PlatformIO project for ESP32 firmware development with ESP-IDF
- Devise message formats for the following types of information using Protobuf:
	1. Timer pulse messages - left blank
	2. LWT messages - includes device ID
	3. Data messages - includes device ID, timestamp, measured temperature, and measured humidity 
- Develop ESP-IDF firmware for the ESP32 that:
	1. Connects to the message broker using the device's username and password
	2. Publishes a LWT message with a 1 minute timeout once authenticated to the broker
	3. Subscribes to the MQTT Pulse Topic
	4. Publishes a data message to the MQTT Data Topic upon receiving a pulse message
	5. Reports placeholder values for measured temperature and humidity
- Use the Wokwi CLI to test the firmware, using the MQTTX tool to:
	1. Issue Pulse messages
	2. Receive LWT and Data messages

### 1b. Local Server
- Install PostgreSQL
- Add the *Data* schema, a *Facility 1* table and user, and an *API* user 
- Set up a Conan + CMake development 
- Develop a containerized data batching application that has:
	1. Deserializes and batches LWT messages before sending a list of device failures to maintenance staff and other community members via a GroupMe chat bot
	2. Deserializes and batches sensor data messages before storing them in a global *Sensor Data* table using the *Facility 1* database user
	3. Utilizes an MQTT user to publish messages to the MQTT Pulse Topic every 500 milliseconds 
- Ensure that the application can save data to the database and sends an GroupMe chat message to maintenance staff when a device disconnects

## 2. Output Subsystem
- Set up a Conan + CMake project and create a C++ gRPC server that uses mTLS for auth
- Set up a Poetry project and create a Python gRPC client
- Add database integration to a *Test* schema with a *Data* table filled with mock data that can be plotted and exported to a CSV or HDF file using Python 
- If this is successful, update project documentation to reflect the change from a JSON API to gRPC. Otherwise, trying creating a REST API using [Crow](https://conan.io/center/recipes/crowcpp-crow). That way, prior knowledge for this project remains CMake, C/C++, Poetry, Python, and SQL

# Release Build
## 1. Input Subsystem
- Purchase ESP32 microcontrollers, breadboards, and DHT11/DHT22 sensors
- Update the ESP-IDF firmware to:
	1. Establish a Wi-Fi connection to the local LAN on device boot
	2. Connect to a message broker deployed on a local Linux dev machine
	3. Reads the room's temperature and relative humidity using a DHT sensor driver
- Connect the ESP32 and DHT sensor together via breadboard
- Flash firmware to the ESP32s
- Reconfigure the containerized local server to send a pulse every 15 minutes instead of every 5 seconds
- Deploy a local server to two devices, where each device represents a facility
- Ensure the input system behaves as intended

## 2. Storage Subsystem
- Determine if deploying a PostgreSQL server locally is more feasible than deploying it in the cloud. Make sure to research hybrid cloud models, where the cloud is only used to support the local hardware
- Deploy the PostgreSQL server. Make sure to update its SSL certs
- Run the Input Subsystem for a few days to ensure that data aggregation is still working correctly

## 3. Output Subsystem
- If the proof-of-concept failed, then start by setting up a local Redis Cache 
- Devise a JSON format that allows the API user to specify:
	- Which facilities to query the data from
	- What conditions to use when querying the data (e.g. timestamp range)
- Develop a headless Phoenix API that: 
	1. Authenticates users via username and password
	2. Returns a JWT to the user and caches the JWT value in a Redis cache for future authentication
	3. Allows the user to query sensor data based on the arguments supplied in a JSON file, ensuring that a valid JWT was sent with the request
	4. Returns the queried data to the user as a CSV of HDF file

# Documentation
## 1. Guide
- Create a step-by-step guide on how to modify and deploy the data aggregation pipeline
## 2. Conclusion and Discussion of Alternatives
- Write a brief discussion post that concludes whether or not this project was a success. This post also discusses alternative solutions and technologies that could be used. 

# Senior Design Expo
- Create a poster that shows design diagrams and relevant photos of the project
- Prepare and practice a presentation speech