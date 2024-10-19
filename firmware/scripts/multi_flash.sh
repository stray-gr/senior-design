#!/bin/bash

# $1 = broker/scripts/users.sh
# $2 = ./config.toml

awk 'NR>1 { print $4, $5 }' $1 | while read line; do
user=$(echo $line | awk '{ print $1 }' | sed 's/name=//')
pass=$(echo $line | awk '{ print $2 }' | sed 's/password=//')
sed -i 's/USER=".*"/USER="'$user'"/' $2
sed -i 's/PASS=".*"/PASS="'$pass'"/' $2
file=$(echo "${user}.bin" | tr -d '"')
cargo espflash save-image --chip esp32 --merge $file --release
done
