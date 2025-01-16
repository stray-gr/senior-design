#!/bin/bash

acl="creds/acl_file"
users="creds/users.txt"
plain="creds/plain.txt"

pass=$(openssl rand -base64 40 | tr -d "=+/" | cut -c1-32)
echo "clock:$pass" >> $users
echo -e "user clock\ntopic write pulse\n" >> $acl

for n in $(seq 1 $1); do
    pass=$(openssl rand -base64 40 | tr -d "=+/" | cut -c1-32)
    echo "dev-$n:$pass" >> $users
    echo -e "user dev-$n\ntopic read pulse\n" >> $acl
    echo -e "user dev-$n\ntopic write data/#\n" >> $acl
done

pass=$(openssl rand -base64 40 | tr -d "=+/" | cut -c1-32)
echo "server:$pass" >> $users
echo -e "user server\ntopic read data/#" >> $acl

chmod 700 $acl
cp $users $plain
chmod 700 $users
mosquitto_passwd -U $users