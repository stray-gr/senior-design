# Overview

# Test Case Descriptions
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
- Purpose: This test ensures that the simulated ESP32 can utilze the protobuf-c library provided by the ESP-IDF framework to serialize and deserialize protobuf messages
- Description: This test will run a unit test that serializes a protobuf message, deseralizes it, and prints the message's fields to stdout
- Inputs: N/A
- Outputs/Results: The values of each protobuf field being printed to stdout
- Normal/Abnormal/Boundary Case Indication: Normal
- Blackbox/Whitebox Test Indication: Blackbox
- Functional/Performance Test Indication: Functional
- Unit/Integration Test Indication: Unit

### PoC-1a-3
- Purpose: This test ensures that the simulated ESP32 can connect to Mosquitto's Public Test Broker
- Description: This test will run the `mqtt_start` method defined in the `mqtt_init` module, which will connect to the broker and subscribe to the *pulse* topic. The MQTTX cli tool will then send a pulse and recieved the published response from the simulated ESP32
- Inputs: URI to a fully functioning MQTT broker, MQTT topic names, MQTT Pulse message sent from MQTTX
- Outputs/Results: Successful retrieval of the published response from the simulated ESP32 via MQTTX
- Normal/Abnormal/Boundary Case Indication: Normal
- Blackbox/Whitebox Test Indication: Whitebox
- Functional/Performance Test Indication: Functional
- Unit/Integration Test Indication: Integration

### PoC-1b-1

### PoC-2-1

### Rel-1-1

### Rel-2-1

### Rel-3-1

# Test Case Matrix