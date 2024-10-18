#!/bin/bash

# $1 = broker/scripts/users.sh
# $2 = ./config.toml

awk 'NR>1 { print $3, $4 }' $1 | while read line; do 
user=$(echo $line | awk '{ print $1 }') 
pass=$(echo $line | awk '{ print $2 }')
sed -i 's/USER=".*"/USER='$user'/' $2
sed -i 's/PASS=".*"/PASS='$pass'/' $2
file=$(echo "${user}.bin" | tr -d '"')
cargo espflash save-image --chip esp32 --merge $file --release
done
