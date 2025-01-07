#!/bin/sh

chmod -R 700 /mosquitto/config/creds/
mosquitto_passwd -U /mosquitto/config/creds/users.txt
echo "hello????"
exec "$@"