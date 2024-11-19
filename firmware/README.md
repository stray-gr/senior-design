# Table of Contents
1. [Installation](#installation)
    - [Prerequisites](#prerequisites)
    - [From Current Repo](#from-current-repo)
    - [From Scratch](#from-scratch)
2. [Wokwi CLI Emulation](#wokwi-cli-emulation)
3. [CBOR Formats](#cbor-formats)

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
2. Download the Mosquitto MQTT Public Test Broker's CA crt from [this link](https://test.mosquitto.org/ssl/mosquitto.org.crt)
3. Move the downloaded crt into the `src` folder and rename it to *ca.crt*
4. Rename [example_config.h](./src/example_config.h) to *config.h*. This header file contains project configuration details and secrets. DO NOT MODIFY for the time being

## From Scratch
To create your own ESP-IDF project using PlatfromIO, follow these steps:
1. [Install](https://docs.platformio.org/en/latest/integration/ide/vscode.html#installation) the PlatformIO IDE Plugin
2. [Create](https://docs.platformio.org/en/latest/tutorials/espressif32/espidf_debugging_unit_testing_analysis.html#setting-up-the-project) an ESP-IDF project
3. Rename [example_config.h](./src/example_config.h) to *config.h*. This header file will contain any project configuration details and secrets. Feel free to make changes
4. Write your firmware in the newly created project. 
5. [Install](https://docs.wokwi.com/wokwi-ci/cli-installation) the Wokwi CLI
6. [Set up](https://docs.wokwi.com/wokwi-ci/cli-usage) the Wokwi CLI. Make sure to include the API token in your shell's environment
7. Ensure you have a [diagram.json](./diagram.json) in your project's root folder. This JSON file will tell the Wokwi API how to set up the hardware for your project.
    > For more information regarding how to customize and configure your own *diagram.json*, refer to [this documentation](https://docs.wokwi.com/diagram-format)
8. Ensure you also have a [wokwi.toml](./wokwi.toml) in your project's root folder. This TOML file will the the Wokwi CLI where your firmware is located

# Wokwi CLI Emulation
To run the Wokwi CLI Emulator:
1. Build the firmware using by clicking the checkmark in the bottom toolbar
2. Open a new terminal and subscribe to the data topic by running the command below:
    ```bash 
    mqttx sub -h test.mosquitto.org -p 8883 -l mqtts -V 5 --ca src/ca.crt -t "6137cde4893c59f76f005a8123d8e8e6"
    ```
3. Open a new terminal and run the `wokwi-cli` command. This will start the simulation, which will listen to the pulse topic and publish to the data topic
4. Open a new terminal and publish to the pulse topic by running the command below. Note that you should have three terminals running now:
    ```bash 
    mqttx pub -h test.mosquitto.org -p 8883 -l mqtts -V 5 --ca src/ca.crt -t "5d4ff171536e1f3c63afcf6709574876" -m ""
    ```
5. Check the terminal subcribed to the data topic for new messages. If you have recieved a "hello there" message, then the emulator is successfully working

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
- Upgrade MQTT to V5
