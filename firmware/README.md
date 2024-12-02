# Table of Contents
1. [Installation](#installation)
    - [Prerequisites](#prerequisites)
    - [From Current Repo](#from-current-repo)
    - [From Scratch](#from-scratch)
2. [Wokwi CLI Emulation](#wokwi-cli-emulation)
3. [Notes](#notes)
4. [CBOR Formats](#cbor-formats)
5. [TODO](#todo)

# Installation
## Prerequisites
Before starting with either form of installation, make sure to install the following software:
- MQTTX CLI tool
- VS Code w/ the PlatformIO IDE VS Code plugin installed
- Wokwi CLI

Here are some useful links for installing the prerequisites:
- Install the [Platform IDE Plugin](https://docs.platformio.org/en/latest/integration/ide/vscode.html#installation)
- Install the [Wokwi CLI](https://docs.wokwi.com/wokwi-ci/cli-installation)
- Set up the [Wokwi CLI](https://docs.wokwi.com/wokwi-ci/cli-usage). Make sure to include the API token in your shell's environment

## From Current Repo
To set up the current ESP-IDF project using PlatformIO:
1. Open the *firmware* folder in VS Code. The PlatformIO plugin should then automatically recognize the project
2. Download the Mosquitto MQTT Public Test Broker's CA cert from [this link](https://test.mosquitto.org/ssl/mosquitto.org.crt)
3. Move the downloaded cert into the `src` folder and rename it to *ca.crt*
4. Rename [example_config.h](./src/example_config.h) to *config.h*. This header file contains project configuration details and secrets. DO NOT MODIFY for the time being

## From Scratch
To create your own ESP-IDF project using PlatfromIO, follow these steps:
1. [Install](https://docs.platformio.org/en/latest/integration/ide/vscode.html#installation) the PlatformIO IDE Plugin
2. [Create](https://docs.platformio.org/en/latest/tutorials/espressif32/espidf_debugging_unit_testing_analysis.html#setting-up-the-project) an ESP-IDF project
3. In your newly created project's [sdkconfig](./sdkconfig.esp32dev), add `CONFIG_MQTT_PROTOCOL_5=y` under the `ESP-MQTT Configurations` section. This will allow you to use MQTT v5
4. Rename [example_config.h](./src/example_config.h) to *config.h*. This header file will contain any project configuration details and secrets. Feel free to make any changes
5. Write your firmware in the newly created project. 
6. [Install](https://docs.wokwi.com/wokwi-ci/cli-installation) the Wokwi CLI
7. [Set up](https://docs.wokwi.com/wokwi-ci/cli-usage) the Wokwi CLI. Make sure to include the API token in your shell's environment
8. Ensure you have a [diagram.json](./diagram.json) in your project's root folder. This JSON file will tell the Wokwi API how to set up the hardware for your project.
    > For more information regarding how to customize and configure your own *diagram.json*, refer to [this documentation](https://docs.wokwi.com/diagram-format)
9. Ensure you also have a [wokwi.toml](./wokwi.toml) in your project's root folder. This TOML file will the the Wokwi CLI where your firmware is located

# Wokwi CLI Emulation
To run the Wokwi CLI Emulator:
1. Build the firmware using by clicking the checkmark in the bottom toolbar
2. Open a new terminal and **subscribe to the *data* topic** by running the command below:
    ```bash 
    mqttx sub -h test.mosquitto.org -p 8883 -l mqtts -V 5 --ca src/ca.crt -t "6137cde4893c59f76f005a8123d8e8e6"
    ```
3. Open a new terminal and **subscribe to the *lwt* topic** by running the command below:
    ```bash 
    mqttx sub -h test.mosquitto.org -p 8883 -l mqtts -V 5 --ca src/ca.crt -t "7ae7ce7048de53dc01e9ecaef1be401e"
    ```
4. Open a new terminal and run the `wokwi-cli --timeout 60000` command. This will start the simulation, which will listen to the pulse topic and publish to the data topic. The simulation will then timeout after 1 minute
5. Open a new terminal and **publish to the *pulse* topic** by running the command below. Note that you should have **four** terminals running by now:
    ```bash 
    mqttx pub -h test.mosquitto.org -p 8883 -l mqtts -V 5 --ca src/ca.crt -t "5d4ff171536e1f3c63afcf6709574876" -m ""
    ```
6. Check the terminal subcribed to the data topic for new messages. If you have recieved a "hello there" message, then the emulator is successfully working
7. Hit `CTRL + C` in the emulator terminal to shut it down. Then wait about 1 minute for the following message to appear in the LWT terminal: *d265f27851d6b048e64576475674922f*. This demonstrates a successful LWT delay
    > It should technically take 3 seconds for the message to display. However, the public message broker being used can take a while to deliver LWT messages

# Notes
- The LWT message is *username* hashed by MD5, which is the username of the emulated device. Additionally, each topic name was also hashed by MD5 to prevent any name collisions with anyone else's topics on the public test broker being used.

# CBOR Formats
### Time Pulse Messages
- **Publisher:** Local Server Chron Job
- **Subscribers:** Each ESP32
- **QoS:** 0
- **Special Properties:** none
- **Payload:** empty

### LWT Messages
- **Publishers:** Each ESP32
- **Subscriber:** Local Server LWT Queue
- **QoS:** 1
- **Special properties:** 1 minute delay
- **Payload:**
    | Field Name | Key |Type | 
    | ---------- | --- | --- |
    | Device ID  | dev | 16 bit unsigned integer |

### Data Messages
- **Publishers:** Each ESP32
- **Subscriber:** Local Server Data Queue
- **QoS:** 1
- **Special properties:** none
- **Payload:**
    | Field Name | Key |Type | 
    | ---------- | --- | --- |
    | Device ID | dev | 16 bit unsigned integer |
    | Temperature | temp | 8 bit signed integer |
    | Relative Humidity | rh | 32 bit float |
    | Unix Epoch (s) | epoch | 32 bit unsigned integer |

# TODO
1. Add protobuf implementations, then replace mention of CBOR
2. Update tasklist and timeline
3. Merge into main branch
4. Remove `fails` and `legacy`
5. Tag main w/ FALL-2024
