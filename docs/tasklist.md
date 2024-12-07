# Proof-of-Concepts
## 1. Input Subsystem
### 1a. Firmware
- Install the following:
	1. PlatformIO IDE and vscode-proto3 plugins for VS Code (WSL)
	2. Protobuf compiler and the protobuf-c pluging (WSL)
	3. Wokwi CLI
	4. The MQTTX CLI Tool
- Set up a RabbitMQ Docker Container 
- Create a PlatformIO project for ESP32 firmware development with ESP-IDF
- Devise message formats for the following types of information using Protobuf:
	1. Timer pulse messages - left blank
	2. LWT messages - includes device ID
	3. Data messages - includes device ID, timestamp, measured temperature, and measured humidity 
- Develop ESP-IDF firmware for the ESP32 that:
	1. Connects to the RabbitMQ broker using the device's username and password
	2. Publishes a LWT message with a 1 minute timeout once authenticated to the broker
	3. Subscribes to the MQTT Pulse Topic
	4. Publishes a data message to the MQTT Data Topic upon receiving a pulse message
	5. Reports placeholder values for measured temperature and humidity
- Use the Wokwi CLI to test the firmware, using the MQTTX tool to:
	1. Issue Pulse messages
	2. Receive LWT and Data messages

### 1b. Local Server
- Install DBeaver
- Set up a Postgres Docker Container that has a global superuser, *Sensor Data* table, and *Mailing List* table
- Create an Elixir dev container for developing a containerized Broadway application that serves as the facility's local server
- Develop a containerized Broadway application that has:
	1. A LWT pipeline that batches LWT messages before sending a list of device failures to maintenance staff via Gmail
	2. A sensor data pipeline that validates live data messages, batches them, and stores them in a global *Sensor Data* table using the Postgres superuser
	3. A cron job which publishes a message to the MQTT Pulse Topic every 5 seconds via a MQTTX CLI script
- Integrate the containerized application with the firmware proof-of-concept
- Ensure that the application can save data to the database and sends an email to maintenance staff when a device disconnects

## 2. Storage Subsystem
- Update the Postgres container to use facility-specific schemas
- Add the *API Users* table
- Set up users for each facility and the API. Note that facility-specific schemas are managed by facility staff and the *API Users* table is managed globally by a sys admin
- Ensure that each facility-specific database user can only:
	- Read and append entries in their  *Sensor Data* table 
	- Read, append, and update entries in their *Mailing List* table
- Ensure that the API's database user can only read from the *Sensor Data* tables of all facilities and update the *API Users* table
- Reconfigure the local server container to use a facility-specific user

# Release Build
## 1. Input Subsystem
- Purchase ESP32 microcontrollers, breadboards, and DHT11/DHT22 sensors
- Update the ESP-IDF firmware to:
	1. Establish a WIFI connection on device boot and 
	2. Use a DHT sensor driver to read temperature and humidity data
- Connect the ESP32 and DHT sensor together via breadboard
- Flash firmware to the ESP32s
- Reconfigure the containerized local server to send a pulse every 15 minutes instead of every 5 seconds
- Deploy a local server to two devices, where each device represents a facility
- Ensure the input system behaves as intended

## 2. Storage Subsystem
- Run the Input Subsystem for a few days to ensure that data aggregation is still working correctly

## 3. Output Subsystem
- Set up a local Redis Cache docker container
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