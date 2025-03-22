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
13. Disable USB pass-through as a precaution before finishing for the day