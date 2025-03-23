# Steps
1. Enable USB pass-through for WSL2 https://learn.microsoft.com/en-us/windows/wsl/connect-usb
2. Install **rust** via `rustup`
3. Install `cargo-binstall`
4. `cargo binstall espup`
5. `cat $HOME/export-esp.sh >> ~/.bashrc` then `source ~/.bashrc`
6. `espup install`
7. Install ESP-IDF Prereqs
8. `cargo install ldproxy`
9. `cargo binstall cargo-generate`
10. `cargo generate esp-rs/esp-idf-template cargo`
    - **TODO: Add instructions**
11. `cargo binstall espflash`
12. `cargo build` or `cargo run`
13. `espflash erase-flash`

# Helpers
Connect:
```bash
mqttx sub -t 2a6e2757e512a3b35aee981c1264992f -V 3.1.1 -h test.mosquitto.org -p 8883 -l mqtts --ca src/mosquitto.org.crt -Pp msg.proto -Pmn Connect
```

Data:
```bash
mqttx sub -t f64893d750df7bacdae2aafa7744e425 -V 3.1.1 -h test.mosquitto.org -p 8883 -l mqtts --ca src/mosquitto.org.crt -Pp msg.proto -Pmn SensorData
```

Pulse:
```bash
mqttx pub -t 5d4ff171536e1f3c63afcf6709574876 -m "" -V 3.1.1 -h test.mosquitto.org -p 8883 -l mqtts --ca src/mosquitto.org.crt
```