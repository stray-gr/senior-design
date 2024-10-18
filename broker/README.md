# Instructions
## Prerequisites
Make sure to have the following software installed:
- Rancher Desktop 
- MQTTX CLI Tool (install via WSL2 if on Windows)

## CA Cert Creation
1. Create the CA private key: `openssl genrsa -des3 -out ca.key 2048`
2. Create the CA cert: `openssl req -new -x509 -days 360 -key ca.key -out ca.crt`

## Message Broker Cert and Private Key Creation
1. Create client private key: `openssl genrsa -out server.key 2048`
2. Create and sign a certificate request using the client's private key: `openssl req -new -out server.csr -key server.key`
    > Make sure to set **Common Name** to the message broker's hostname. In this case, **test-broker** was used
3. Using a CA cert and key, create the client cert: `openssl x509 -req -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out server.crt -days 180`

## Docker Build
First, move the previously generated certs and keys into a *certs* folder. Then run the following commands: 
```bash
docker build -t broker .
docker run --rm --hostname test-broker -p 1883:1883 broker
```

## MQTT Pub/Sub
Below are commands to subscribe and publish to the `pulse` topic using the MQTTX CLI tool:
```bash
wget http://localhost:15672/cli/rabbitmqadmin
chmod +x rabbitmqadmin
./rabbitmqadmin declare user name={Dev ID} password={PSK} tags=administrator
./rabbitmqadmin declare permission vhost="/" user={DEV ID} configure=".*" write=".*" read=".*"
mqttx sub -t 'pulse' -h 'localhost' -p 1883 -V 5 --username {Dev ID} --password {PSK}
mqttx pub -t 'pulse' -h 'localhost' -p 1883 -V 5 --username {Dev ID} --password {PSK} -m "hello there"
```

# Dockerfile explanation

# Notes

- http://www.steves-internet-guide.com/creating-and-using-client-certificates-with-mqtt-and-mosquitto/
- http://www.steves-internet-guide.com/mosquitto-tls/
- rumqttc w/ client certs: https://github.com/bytebeamio/rumqtt/blob/main/rumqttc/examples/tls2.rs
- Make sure to use rumqttc v5

# TODO
1. Create script that uses `rabbitmqadmin` to declare users, queues, and bindings after docker start
2. Update `firmware/scripts/save_images.sh` to use new script format
3. Add TLS