# Team GR IoT Data Pipeline Template Test Plan

## Overview
Due to how multiple components within the project need to communicate with one another, the main focus of this project's testing is integration testing. This ensures that each component will interface with other components in a predictable and correct way. The process of integration may also highlight how certain project processes can be automated to make integration testing and end deployment more reproducible. Such a relization can then lead to additional project refinements.

Some components, however, are composed of complex features that need additional unit testing. An example can be seen with the database connection pool semaphore used by the batching app and gRPC API. If this semaphore implementation were to be faulty, then an unsustainable amount of database connection slots could be created and lead to performance issues within the components that utilize it. This is were unit testing will be used to ensure that any complex functionality within each component also behaves as intended.

## Test Case Descriptions
### PoC-1a-1
- Purpose: This test ensures that the simulated ESP32 can connect to Wi-Fi
- Description: This test will run the `wifi_connect` method defined in the `net_init` module 
- Inputs: N/A
- Outputs/Results: Successful connection to the Wokwi-GUEST virtual LAN
- Normal/Abnormal/Boundary Case Indication: Normal
- Blackbox/Whitebox Test Indication: Whitebox
- Functional/Performance Test Indication: Functional
- Unit/Integration Test Indication: Integration

### PoC-1a-2
- Purpose: This test ensures that the simulated ESP32 can connect to Mosquitto's Public Test Broker
- Description: This test will run the `mqtt_start` method defined in the `mqtt_init` module, which will connect to the broker and subscribe to the *pulse* topic. The MQTTX cli tool will then send a pulse to the simulated ESP32 and recieve response published by said ESP32
- Inputs: URI to a fully functioning MQTT broker, MQTT topic names, MQTT Pulse message sent from MQTTX
- Outputs/Results: Successful retrieval of the published message from the simulated ESP32 via MQTTX
- Normal/Abnormal/Boundary Case Indication: Normal
- Blackbox/Whitebox Test Indication: Whitebox
- Functional/Performance Test Indication: Functional
- Unit/Integration Test Indication: Integration

### PoC-1a-3
- Purpose: This test ensures that the simulated ESP32 can utilze the protobuf-c library provided by the ESP-IDF framework to serialize and deserialize protobuf messages
- Description: This test will run a unit test that serializes a protobuf message, deseralizes it, and prints the message's fields to stdout
- Inputs: N/A
- Outputs/Results: The values of each protobuf field being printed to stdout
- Normal/Abnormal/Boundary Case Indication: Normal
- Blackbox/Whitebox Test Indication: Blackbox
- Functional/Performance Test Indication: Functional
- Unit/Integration Test Indication: Unit

### PoC-1b-1
- Purpose: This test ensures that the Conan + CMake development environment can be set up on another Unix-based machine with a different system environment
- Description: This test will involve setting up the development environment on a laptop running Lubuntu 24.04, which will have a slightly different system environemt than the Ubuntu 24.04 WSL environment being primarily used
- Inputs: N/A
- Outputs/Results: The development environment is able to build project executables in both system environments
- Normal/Abnormal/Boundary Case Indication: Boundary
- Blackbox/Whitebox Test Indication: Blackbox
- Functional/Performance Test Indication: Functional
- Unit/Integration Test Indication: Integration

### PoC-1b-2
- Purpose: This test ensures that the database connection pool's semaphore, located in the `server_callbacks` module, will force threads to wait when no resources are available
- Description: This unit test will set the database connection pool size to 1 before spawing 2 threads. Each thread will then log when they reserve a connection pool slot and release it. These logs should occur in series, with the 2nd thread aquiring a slot only after the first thread releases the slot.  
- Inputs: Database connection pool size
- Outputs/Results: Logs from each thread that DO NOT overlap with one another
- Normal/Abnormal/Boundary Case Indication: Boundary
- Blackbox/Whitebox Test Indication: Whitebox
- Functional/Performance Test Indication: Functional
- Unit/Integration Test Indication: Unit

### PoC-1b-3
- Purpose: This integration test ensures that the Postgresql database container, Mosquitto broker container, local server containers, and the project's test client can successfully transfer data to the database and send outage reports to a GroupMe chat  
- Description: This test will utlize the `compose.yaml` to start all containers. From there, the test client will be ran locally before restarting the local server's *clock* container. The client will then disconnect. If successful, 5 new rows should be added to the database and an outage report of 1 device should be sent to the GroupMe 
- Inputs: N/A
- Outputs/Results: New database data entries and an outage report being sent to the GroupMe
- Normal/Abnormal/Boundary Case Indication: Normal
- Blackbox/Whitebox Test Indication: Blackbox
- Functional/Performance Test Indication: Functional
- Unit/Integration Test Indication: Integration

### PoC-2-1
- Purpose: This integration test ensures that the gRPC service will only accept mTLS with a valid client cert for authentication
- Description: This test will utilize the gRPC test client, which is configured to connect with valid and invalid certs. Only the RPC call using valid certs should succeed
- Inputs: Valid and invalid PEM certs
- Outputs/Results: Results from the RPC call, followed by a message saying "All tests have passed"
- Normal/Abnormal/Boundary Case Indication: Boundary
- Blackbox/Whitebox Test Indication: Blackbox
- Functional/Performance Test Indication: Functional
- Unit/Integration Test Indication: Integration

### PoC-2-2
- Purpose: This test ensures that the database connection pool's semaphore, located in the `service_callbacks` module, will force RPC callbacks to wait when no resources are available
- Description: This unit test will set the database connection pool size to 1. From there, a test client will make 2 sequential RPC calls. One of the two RPC callbacks will then have to wait for a database connect slot to free up, and will log when the waiting begins
- Inputs: 2 RPC calls
- Outputs/Results: Results from each RPC call, along with logs from the callback that waited for a connection slot
- Normal/Abnormal/Boundary Case Indication: Boundary
- Blackbox/Whitebox Test Indication: Whitebox
- Functional/Performance Test Indication: Functional
- Unit/Integration Test Indication: Unit

### PoC-2-3
- Purpose: This test ensures that results streamed from the database upon RPC callback are consumed correctly by the callback
- Description: This test will ensure that each callback removes each streamed result from the result queue by logging the queue's size before each gRPC write. The final reported size should be 0
- Inputs: An RPC call
- Outputs/Results: Logs from the RPC call, reporting the result queue's size before each gRPC write
- Normal/Abnormal/Boundary Case Indication: Normal
- Blackbox/Whitebox Test Indication: Whitebox
- Functional/Performance Test Indication: Functional
- Unit/Integration Test Indication: Integration

### Rel-1-1
- Purpose: This test ensures that each ESP32 can connect to the LAN
- Description: This test will involve using a serial terminal to monitor output generated from the device after running the `wifi_connect` method defined in the `net_init` module
- Inputs: N/A
- Outputs/Results: Successful connection to the LAN
- Normal/Abnormal/Boundary Case Indication: Normal
- Blackbox/Whitebox Test Indication: Whitebox
- Functional/Performance Test Indication: Functional
- Unit/Integration Test Indication: Integration

### Rel-1-2
- Purpose: This test ensures that the each ESP32 can connect to the Mosquitto broker deployed to a local development machine
- Description: This test requires opening a port on a local development machine and starting the broker container. Each ESP32 will then connect to the broker via the `mqtt_start` method defined in the `mqtt_init` module. The MQTTX cli tool will then send a pulse to the each ESP32 via the broker and recieve the published responses 
- Inputs: URI to a fully functioning MQTT broker, MQTT topic names, MQTT Pulse message sent from MQTTX
- Outputs/Results: Successful retrieval of the published messages from each ESP32 via MQTTX
- Normal/Abnormal/Boundary Case Indication: Normal
- Blackbox/Whitebox Test Indication: Whitebox
- Functional/Performance Test Indication: Functional
- Unit/Integration Test Indication: Integration

### Rel-1-3
- Purpose: This test ensures that the each ESP32 can reconnect to the broker after temporarily loosing connection
- Description: This test will be conducted by restarting the broker while each ESP32 is connected. The logs from the newly restarted broker should then show each device reconnecting
- Inputs: N/A
- Outputs/Results: Broker logs showing each device reconnecting
- Normal/Abnormal/Boundary Case Indication: Abnormal
- Blackbox/Whitebox Test Indication: Whitebox
- Functional/Performance Test Indication: Functional
- Unit/Integration Test Indication: Integration

### Rel-1-4
- Purpose: This test ensures that the ESP32 firmware and DHT series sensors can accurately report temperature and relative humidity (RH)
- Description: This test requires deploying an ESP32 to an outdoor environment (e.g. a garage) to collect temperature and RH data and compare the readings to local weather forcasts
- Inputs: Local weather forcast
- Outputs/Results: Comparison between the weather forcast and the readings collected
- Normal/Abnormal/Boundary Case Indication: Normal
- Blackbox/Whitebox Test Indication: Whitebox
- Functional/Performance Test Indication: Performance
- Unit/Integration Test Indication: Integration

### Rel-1-5
- Purpose: This test ensures that the breadboards being used by each ESP32 won't short the devices
- Description: This test requires inserting jumper cables on each half/partition of the breadboard and ensuring that the rows of each half are discontinuous by using a multimeter to test for continuity 
- Inputs: A jumper cable on each partition, such that each jumper cable is on the same row
- Outputs/Results: A discontinuous reading from the multimeter when each probe is held to a corresponding jumper cable
- Normal/Abnormal/Boundary Case Indication: Abnormal
- Blackbox/Whitebox Test Indication: Blackbox
- Functional/Performance Test Indication: Functional
- Unit/Integration Test Indication: Integration

### Rel-3-1
- Purpose: This test ensures that each gRPC endpoint can reproducibly return results
- Description: This test involves creating a mock data table filled with predetermined data entries. From there, a unit test will ensure that the results of each RPC call matched the expected results
- Inputs: Mock data table
- Outputs/Results: Unit test successes reported by the GoogleTest framework 
- Normal/Abnormal/Boundary Case Indication: Normal
- Blackbox/Whitebox Test Indication: Whitebox
- Functional/Performance Test Indication: Functional
- Unit/Integration Test Indication: Unit

## Test Case Matrix
| Test Case ID          | Normal/Abnormal/Boundary | Blackbox/Whitebox | Functional/Performance | Unit/Integration |
| --------------------- | ------------------------ | ----------------- | ---------------------- | ---------------- | 
| [PoC-1a-1](#poc-1a-1) | Normal                   | Whitebox          | Functional             | Integration      |
| [PoC-1a-2](#poc-1a-2) | Normal                   | Whitebox          | Functional             | Integration      |
| [PoC-1a-3](#poc-1a-3) | Normal                   | Blackbox          | Functional             | Unit             |
| [PoC-1b-1](#poc-1b-1) | Boundary                 | Blackbox          | Functional             | Integration      |
| [PoC-1b-2](#poc-1b-2) | Boundary                 | Whitebox          | Functional             | Unit             |
| [PoC-1b-3](#poc-1b-3) | Normal                   | Blackbox          | Functional             | Integration      |
| [PoC-2-1](#poc-2-1)   | Boundary                 | Blackbox          | Functional             | Integration      |
| [PoC-2-2](#poc-2-2)   | Boundary                 | Whitebox          | Functional             | Unit             |
| [PoC-2-3](#poc-2-3)   | Normal                   | Whitebox          | Functional             | Integration      |
| [Rel-1-1](#rel-1-1)   | Normal                   | Whitebox          | Functional             | Integration      |
| [Rel-1-2](#rel-1-2)   | Normal                   | Whitebox          | Functional             | Integration      |
| [Rel-1-3](#rel-1-3)   | Abnormal                 | Whitebox          | Functional             | Integration      |
| [Rel-1-4](#rel-1-4)   | Normal                   | Whitebox          | Performance            | Integration      |
| [Rel-1-5](#rel-1-5)   | Abnormal                 | Blackbox          | Functional             | Integration      |
| [Rel-3-1](#rel-3-1)   | Normal                   | Whitebox          | Functional             | Unit             |
