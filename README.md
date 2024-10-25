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
## Rust ESP32 Firmware Development
Unfortunately, using xtensa prevents the following MQTT cargo crates from working due to the environment's constraints:
- rumqttc   - only fails with TLS enabled (rustls fails, native-tls requires openssl)
- ntex-mqtt - relies on Linux Signals
- paho-mqtt - the paho mqtt c bindings use an rlib, which ends up being unrecognized here

The same goes for the RISCV boards, except rumqttc fails only because the environment fails to find `riscv32-esp-elf-gcc`. This is peciluar since the set up for ESP32 RISCV boards required the LLVM toolchain to be installed, not GCC. On another note, the esp-idf-svc crate has an MQTT implementation. However, it lacks TLS and MQTT v5 support. 

As for development using no_std crates, the following issues were encountered:
- Using embedded-tls and rust-mqtt in a std xtensa environment led to the firmware binaries being too big. This seem to be an issue with the `cargo espflash` tool, where version 3 won't automatically resize the app partition. Though version 2 of this tool doesn't have this issue, it fails to build with the most recent version of Rust being used by the development environment.
- Using embedded-tls and rust-mqtt in a no_std xtensa environment will actually build. However, rust-mqtt only works with TCP sockets and is not interoperable with embedded-tls. At least embedded-tls works though. This means TCP/HTTP applications can utilize TLS via the embedded-tls crate in such a constrained environment.

 Additionally, the dev container approach can very slow in a std environment since the esp-idf-sys crate will need to rebuild every time project dependencies are edited in the *Cargo.toml* file. In conclusion, Rust still isn't quite ready for major IoT development. This means that Rust firmware will have to use unencrypted MQTT and will need to be developed locally on WSL if a std environment is needed. The following alternatives have since been considered (listed in order of preference):
- Arduino with wolfSSL and wolfMQTT - C++, MQTT v5 
- ESP-IDF - C, MQTT v5
- micropython - python, MQTT v3.1
- atomvm - erlang, MQTT v3.1

Note that all alternatives have DHT sensor drivers available, with the ESP-IDF and Arduino options each need their own 3rd party driver.

## Licensing
- This repo was licensed under the MIT license because it:
    1. Protects any related documenation
    2. Is compatible with the Rust and Python packages being used
    3. Would allow a company to freely use the data pipeline template that this repo will eventually outline