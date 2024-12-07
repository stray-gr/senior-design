#!/bin/bash

# Install ESP Qemu
if ! [ -d ./qemu ]; 
then
    wget https://github.com/espressif/qemu/releases/download/esp-develop-9.0.0-20240606/qemu-xtensa-softmmu-esp_develop_9.0.0_20240606-x86_64-linux-gnu.tar.xz -O qemu-xtensa.tar.xz
    tar -xvf qemu-xtensa.tar.xz
    rm qemu-xtensa.tar.xz
else
    echo "$(pwd)/qemu already exists"
fi
