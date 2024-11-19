# Table of Contents
1. [Project Description](./docs/project_description.md)
2. [User Stories](./docs/user_stories.md)
3. Design Diagrams
    - [Level 0](./docs/design_diagrams/D0.pdf)
    - [Level 1](./docs/design_diagrams/D1.pdf)
    - [Level 2](./docs/design_diagrams/D2.pdf)
4. Project Tasks and Timeline
    - [Task List](./docs/tasklist.md)
    - [Time Line](./docs/timeline.md)
5. [ABET Concerns Essay](./docs/essays/constraints-essay-gr.pdf)
6. [PPT Slideshow](./docs/presentations/Midterm_Presentation.pdf)
7. Self-Assessment Essays
    - [Team Contract](./docs/essays/team-contract-gr.pdf)
    - [Capstone Assessment](./docs/essays/capstone-assessment-gr.pdf)
8. [Professional Bio](./docs/bio_rodriguez.md)
9. [Budget](#budget)
10. [Appendix](#appendix)

### Note:
- Since this is a solo project, the *Effort Matrix* assignment was skipped. 

# Budget
- TBD

# Appendix
## FAQ
**What is going to be viewed to the user? Is the API going to have a search feature that then returns what the user wants to see or will they be able to see all the data?**
- First, the user sends a data query in the form of a JSON file which has fields that filter the data (e.g. filter by datetime). From there, the API returns an HDF or CSV file 
where the columns will be the database columns and the rows are the matching data entries. This is all done headlessly, meaning there isn't any direct visualization support. Lastly,
the API user can query sensor data from ANY facility. This means they could see all of the sensor data ever collected if desired.

**Will the central database and API be hosted as a cloud service?**
- This project will locally host the central database and API to save on long term cost. However, some research and discussion will be done regarding cloud deployment as an alternative. 

**Why were RabbitMQ and MQTT were chosen for the message broker?**
- MQTT is an IoT-focused protocol that makes it easy to send messages to a high volume of clients using the PUB/SUB model. With the PUB/SUB model, clients subscribe to a channel/topic 
that is managed by a message broker. From there, publishers can send messages to the message broker over a specific topic. The broker will then forward the published message to
each client subscribed to the topic on behalf of the publisher. This simplifies the development and debugging of the project's network infrastructure, as the responsibility of receiving 
and forwarding messages is now on the message broker rather than the developer. 
- The only reason RabbitMQ was chosen as the message broker was because the *Broadway* framework being used has pre-made middleware for RabbitMQ. Otherwise, the Mosquitto MQTT broker 
would've been used due to its ease of configuration.

**What benefits does this pipeline have over other pre-existing solutions?**
- The idea of this pipeline is to be more developer friendly than other solutions that place restrictions on what can be done. This developer-centric approach would allow developers to 
have an easier time configuring and extending their pipeline without having limitations forced upon them.

## Rust ESP32 Firmware Development
Initially, this project planned on using the Rust ESP32 toolchains developed by the esp-rs organization to implement any IoT firmware needed. Unfortunately, using their std toolchain for Xtensa boards prevents the following MQTT cargo crates from working due to the toolchain's limited support:
- rumqttc   - only fails with TLS enabled (the toolchain fails to build rustls, native-tls requires openssl)
- ntex-mqtt - relies on Linux Signals
- paho-mqtt - the paho mqtt c bindings use an rlib, which ends up being unrecognized by the toolchain

The same issues are encountered when using the std toolchain for RISCV boards. However, rumqttc fails only because the environment fails to find `riscv32-esp-elf-gcc`. This is odd since the toolchain required the LLVM toolchain to be installed, not GCC. The only other alternative found was the esp-idf-svc crate developed by the esp-rs organization. Though this crate works fine with either toolchain, their MQTT implementation lacks TLS and MQTT v5 support. This marked a dead end for using std crates with either toolchain.

As for development using no_std crates, the following issues were encountered:
- Using embedded-tls and rust-mqtt with the std xtensa toolchain led to the firmware binaries being too big. This seem to be an issue with the `cargo espflash` tool, where version 3 won't automatically resize the app partition. Though version 2 of this tool doesn't have this issue, it fails to build with the most recent version of Rust being used by the development environment.
- Using embedded-tls and rust-mqtt with a completely no_std xtensa toolchain will actually build. However, rust-mqtt only works with TCP sockets and is not interoperable with embedded-tls. At least embedded-tls works though. This means TCP/HTTP applications can utilize TLS via the embedded-tls crate in such a constrained environment.

Asides from toolchain issues, using dev containers for the development environment itself approach can very slow when using a std toolchain. This is due to the esp-idf-sys crate needing to rebuild every time project dependencies are updated in the *Cargo.toml* file. In conclusion, Rust still isn't quite ready for major IoT development. Rust firmware using toolchains created by the esp-rs organization will have to use unencrypted MQTT and will need to be developed locally on WSL if a std environment is desired. Hopefully, interoperability between their toolchains and the 3rd party crates that were tested will improve in the near future.

Next, the following alternatives were considered (listed in order of preference). Note that all of these alternatives have DHT sensor drivers available:
- Arduino with wolfSSL and wolfMQTT - written in C++ and supports MQTT v5 
- ESP-IDF - written in C and supports MQTT v5
- MicroPython - written in Python and supports MQTT v3.1
- AtomVm - written in Erlang and supports MQTT v3.1

Out of these options, the ESP-IDF SDK was selected due to the following reasons:
1. The PlatformIO IDE plugin for VS Code automates the installation and creation up of new ESP-IDF projects, making development environment set-up easier 
2. ESP-IDF projects have a wide variety of plugins, called [components](https://components.espressif.com/), that make adding new functionality to your project easier. For example, a DHT22 sensor driver component could be installed and linked into the firmware with relative ease
3. There's plenty of docmentation regarding the ESP-IDF SDK, along with decent error reporting
4. The SDK is licensed under the permissive Apache-2.0 license

Though developing firmware with the Arduino SDK would resulted in source code with easier to read syntax, wolfSSl and wolfMQTT both use the GPL-2.0 license without the GPL linking exception. This would require that ANY firmware created for this project would need to be licensed under GPL-2.0 as well.

## Licensing
- This repo was licensed under the MIT license because it:
    1. Protects any related documenation
    2. Is compatible with the Rust and Python packages being used
    3. Would allow a company to freely use the data pipeline template that this repo will eventually outline