#!/bin/bash

# Make sure creds/ exists
if [ ! -d "creds/" ]; then
    mkdir creds
else
    rm creds/*
fi

# File endpoints
acl="creds/acl_file"
users="creds/users.txt"
plain="creds/plain.txt"

# Client user
pass=$(openssl rand -base64 40 | tr -d "=+/" | cut -c1-32)
echo "client:$pass" >> $users
echo -e "user client\ntopic write connect\n" >> $acl
echo -e "user client\ntopic read pulse\n" >> $acl
echo -e "user client\ntopic write data/#\n" >> $acl

# Clock user
pass=$(openssl rand -base64 40 | tr -d "=+/" | cut -c1-32)
echo "clock:$pass" >> $users
echo -e "user clock\ntopic write pulse\n" >> $acl

# Proxy user
pass=$(openssl rand -base64 40 | tr -d "=+/" | cut -c1-32)
echo "proxy:$pass" >> $users
echo -e "user proxy\ntopic read #\n" >> $acl

# Device users
for n in $(seq 1 $1); do
    pass=$(openssl rand -base64 40 | tr -d "=+/" | cut -c1-32)
    echo "dev-$n:$pass" >> $users
    echo -e "user dev-$n\ntopic write connect\n" >> $acl
    echo -e "user dev-$n\ntopic read pulse\n" >> $acl
    echo -e "user dev-$n\ntopic write data/#\n" >> $acl
done

chmod 700 $acl
cp $users $plain
chmod 700 $users
mosquitto_passwd -U $users