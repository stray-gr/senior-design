# Completion of Proof-of-Concepts
## 1. Input Subsystem 
- To reach this milestone, the tasks listed for the [Firmware](./tasklist.md#1a-firmware) Proof-of-Concept must be completed. The following documentation must also be completed:
	- An explanation of how to set up the Mosquitto MQTT Broker and its users
	- An guide on how to build and configure the PlatformIO project
	- Protobuf definitions of the message formats used by the ESP32s and local server
	- An overview of how to configure and test the firmware, especially in regard to setting sensitive environment variables in the firmware
- Additionally, the tasks listed for the [Local Server](./tasklist.md#1b-local-server) Proof-of-Concept must be completed. The following documentation must also be completed:
	- An explanation of how to configure deploy a local a PostgreSQL server
	- Documentation listing out the various database schemas and tables, along with what permissions each user has
	- A guide on how to set up the Conan + CMake project, build the server's executables, and test them
- Deliverables will include:
	1. A PostgreSQL Database with facility-specific schemas and database users with access control restrictions
	2. ESP-IDF firmware that can run on an ESP32 via the Wokwi CLI, report placeholder data for its sensor readings
	3. A local server that can aggregate data into a facility-specific sensor data table and can notify maintenance staff of any device failures

## 2. Output Subsystem
- To reach this milestone, the tasks listed for the [Output Subsystem](./tasklist.md#2-output-subsystem) Proof-of-Concept must be completed. Documentation detailing whether gRPC was a success and how it was set up must also be completed.

# Completion of Release Build
## 1. Input Subsystem
- To reach this milestone, the tasks listed for the [Input Subsystem](./tasklist.md#1-input-subsystem-1) Release Build must be completed. Note that purchasing the hardware will be the most crucial task during this phase. The following documentation must also be completed:
	- A diagram of how the hardware was set up
	- Instructions on how to flash the firmware to the devices and deploy them
	- A  guide on how to deploy the local server to a machine on the LAN
- Deliverables will include:
	1. Fully functional IoT devices capable of reading and relaying sensor data
	2. A deployed local server

## 2. Storage Subsystem
- To reach this milestone, the tasks listed for the [Storage Subsystem](./tasklist.md#2-storage-subsystem) Release Build must be completed.
- Deliverables will include:
	1. A deployed PostgreSQL server
	2. Documentation detailing why the given deployment method was selected
	3. Tables populated with sensor data aggregated over the course of a few days

## 3. Output Subsystem
- To reach this milestone, the tasks listed for the [Output Subsystem](./tasklist.md#3-output-subsystem) Release Build must be completed. The following documentation must also be completed:
	- An explanation of the Redis container's Dockerfile
	- Diagrams of the JSON and CSV/HDF format used by the API
	- A high-level overview of how the containerized API works, especially in regard to authentication
	- Examples of how to send a JWT with the request for authentication
- Deliverables will include a headless Phoenix API that allows authenticated users to query sensor data.

# Completion of Documentation Milestone
- To reach this milestone, the tasks listed for the [Guide](./tasklist.md#1-guide) and [Conclusion](./tasklist.md#2-conclusion-and-discussion-of-alternatives) must be completed.
- Deliverables will include:
	1. A guide on how to modify and deploy the data aggregation pipeline
	2. A project conclusion that includes a discussion of alternatives
  
# Preparation for the Expo
- To reach this milestone, all of the tasks listed for the [Senior Design Expo](./tasklist.md#senior-design-expo) need to be completed.
- Deliverables will include a presentation poster, along with an accompanying speech.