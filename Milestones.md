# Completion of Proof-of-Concepts
## 1. Input Subsystem Milestone
- To reach this milestone, the tasks listed for the [Firmware](./Tasklist.md#1a-firmware) Proof-of-Concept must be completed. The following documentation must also be completed:
	- An explanation of the RabbitMQ container's Dockerfile, along with an explanation of any additional steps needed to set up the container
	- A brief explanation of how to run and configure the Rust dev container
	- A diagram of the message formats used by the ESP32s and local server
	- An overview of how to configure and test the firmware, especially in regard to setting sensitive environment variables in the firmware
- Additionally, the tasks listed for the [Local Server](./Tasklist.md#1b-local-server) Proof-of-Concept must be completed. The following documentation must also be completed:
	- An explanation of the Postgres container's Dockerfile
	- A brief explanation of how to run and configure the Elixir dev container
	- A high-level overview of how the containerized local server works, along with additional explanation of its Dockerfile and how the cron job was set up
	- Instructions on how to test and locally deploy the server
- Deliverables will include:
	1. Rust firmware that can run on an ESP32 Qemu emulator, report randomized data for its sensor readings, and communicate via ethernet
	2. A containerized local server that can aggregate data into a global *Sensor Data* table and can email maintenance of any device failures
	3. A simplified Postgres Database with a global *Sensor Data* and *Mailing list* table
	
## 2. Storage Subsystem Milestone
- To reach this milestone, the tasks listed for the [Storage Subsystem](./Tasklist.md#2-storage-subsystem) Proof-of-Concept must be completed. The following documentation must also be completed:
	- A guide listing out the various database schemas and tables, along with what permissions each user has
	- Instructions on how to configure and deploy the containerized local server for a given facility
- Deliverables will include:
	1. A Postgres Database with facility-specific schemas, an *API Users* table, and database users with specific permissions
	2. An updated local server container image that utilizes a facility-specific user to access their facility's schema

# Completion of Release Build
## 1. Input Subsystem
- To reach this milestone, the tasks listed for the [Input Subsystem](./Tasklist.md#1-input-subsystem-1) Release Build must be completed. Note that purchasing the hardware will be the most crucial task during this phase. The following documentation must also be completed:
	- A diagram of how the hardware was set up
	- Instructions on how to flash the firmware to the devices and deploy them
	- A brief guide on how the firewalls for each deployed server were set up, along with where to find more information
- Deliverables will include:
	1. Fully functional IoT devices capable of reading and relaying sensor data
	2. Local servers deployed on two devices 

## 2. Storage Subsystem
- To reach this milestone, the tasks listed for the [Storage Subsystem](./Tasklist.md#2-storage-subsystem-1) Release Build must be completed.
- Deliverables will include sensor data aggregated over the course of a few days.

## 3. Output Subsystem
- To reach this milestone, the tasks listed for the [Output Subsystem](./Tasklist.md#3-output-subsystem) Release Build must be completed. The following documentation must also be completed:
	- An explanation of the Redis container's Dockerfile
	- Diagrams of the JSON and CSV/HDF format used by the API
	- A high-level overview of how the containerized API works, especially in regard to authentication
	- Examples of how to send a JWT with the request for authentication
- Deliverables will include a headless Phoenix API that allows authenticated users to query sensor data.

# Completion of Documentation Milestone
- To reach this milestone, the tasks listed for the [Guide](./Tasklist.md#1-guide) and [Conclusion](./Tasklist.md#2-conclusion-and-discussion-of-alternatives) must be completed.
- Deliverables will include:
	1. A guide on how to modify and deploy the data aggregation pipeline
	2. A project conclusion that includes a discussion of alternatives
  
# Preparation for the Expo
- To reach this milestone, all of the tasks listed for the [Senior Design Expo](./Tasklist.md#senior-design-expo) need to be completed.
- Deliverables will include a presentation poster, along with an accompanying speech.