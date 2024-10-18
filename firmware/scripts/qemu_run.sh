#!/bin/bash

cargo espflash save-image --chip esp32 --merge out.bin --release
./qemu/bin/qemu-system-xtensa -nographic -machine esp32 -drive file=out.bin,if=mtd,format=raw -m 4M
