# Instructions
## Prerequisites
Make sure to have the following software installed:
- Rancher Desktop 
- MQTTX CLI Tool (install via WSL2 if on Windows)

## CA Cert Creation
1. Create the CA private key: `openssl genrsa -des3 -out ca.key 2048`
2. Create the CA cert: `openssl req -new -x509 -days 360 -key ca.key -out ca.crt`

## Server Cert and Private Key Creation
1. Create client private key: `openssl genrsa -out server.key 2048`
2. Create and sign a certificate request using the client's private key: `openssl req -new -out server.csr -key server.key`
    > Make sure to set **Common Name** to the device's ID
3. Using a CA cert and key, create the client cert: `openssl x509 -req -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out server.crt -days 180`

## Docker Build
```bash
docker build -t broker .
docker run --rm --hostname test-broker -p 8883:8883 broker
```

## MQTT Pub/Sub
```bash
mqttx sub -t 'pulse' -h 'localhost' -p 8883 -V 5
mqttx pub -t 'pulse' -h 'localhost' -p 8883 -V 5 -m "hello there"
```

# Dockerfile explanation

# Notes

- http://www.steves-internet-guide.com/creating-and-using-client-certificates-with-mqtt-and-mosquitto/
- http://www.steves-internet-guide.com/mosquitto-tls/
- rumqttc w/ client certs: https://github.com/bytebeamio/rumqtt/blob/main/rumqttc/examples/tls2.rs
- Make sure to use rumqttc v5

# TODO
1. Update docker image to run `users.sh` and `queues.sh`... https://stackoverflow.com/a/30773882