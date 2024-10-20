# Table of Contents
1. [Prerequisites](#prerequisites)
2. [Dockerfile Explanation](#dockerfile-explanation)
3. [Docker Container Creation](#docker-container-creation)
4. [RabbitMQ User Creation](#rabbitmq-user-creation)
5. [MQTTX Pub/Sub](#mqttx-pubsub)

# Prerequisites
Make sure to have the following software installed:
- Rancher Desktop 
- MQTTX CLI Tool (install via WSL2 if on Windows)
- tcpdump (install via WSL2 if on Windows)

# Dockerfile Explanation

# Docker Container Creation
First, create a CA cert and private key:
1. Create the CA private key: `openssl genrsa -des3 -out ca.key 2048`
2. Create the CA cert: `openssl req -new -x509 -days 360 -key ca.key -out ca.crt`

Next, create a cert and private key for the server to use for TLS:
1. Create client private key: `openssl genrsa -out server.key 2048`
2. Create and sign a certificate request using the client's private key: `openssl req -new -out server.csr -key server.key`
    > Make sure to set **Common Name** to the message broker's hostname. In this case, *localhost* was used for development purposes
3. Using a CA cert and key, create the client cert: `openssl x509 -req -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out server.crt -days 180`

Finally, move the previously generated certs and keys into a *certs* folder. Then run the following commands: 
```bash
docker build -t broker .
docker run --rm --hostname localhost -p 8883:8883 -it broker
```

# RabbitMQ User Creation
First, find the docker container ID of the *broker* container using `docker ps`. Then open a bash shell using `docker exec -it {ID} bash`. This shell will be used to create users below.

To create an MQTT subscriber:
```bash
rabbitmqctl add_user {NAME} {PASSWORD}
rabbitmqctl set_permissions -p / {NAME} "^mqtt-sub.*$" "^mqtt-sub.*$" ".*"
```

To create an MQTT publisher:
```bash
rabbitmqctl add_user {NAME} {PASSWORD}
rabbitmqctl set_permissions -p / {NAME} "^mqtt-sub.*$" ".*" "^mqtt-sub.*$" 
```

To create an MQTT subscriber and publisher:
```bash
rabbitmqctl add_user {NAME} {PASSWORD}
rabbitmqctl set_permissions -p / {NAME} "^mqtt-sub.*$" ".*" ".*" 
```

To create a general purpose user:
```bash
rabbitmqctl add_user {NAME} {PASSWORD}
rabbitmqctl set_permissions -p / {NAME} ".*" ".*" ".*" 
```

# MQTTX Pub/Sub
Subscribe to an MQTT topic using: 
```bash 
mqttx sub -h localhost -p 8883 -l mqtts -V 5 --ca broker/certs/ca.crt -u {NAME} -P {PASSWORD} -t "{TOPIC}"
```

Publish messages to an MQTT topic using: 
```bash 
mqttx pub -h localhost -p 8883 -l mqtts -V 5 --ca broker/certs/ca.crt -u {NAME} -P {PASSWORD} -t "{TOPIC}" -m "msg"
```

To ensure that MQTT traffic is being encrypted, you can use `sudo tcpdump -i lo -A | grep 'msg'` 
- This command will sniff local TCP traffic for anything containing "msg"
- If the output of this command doesn't reveal any captured packets, then TLS is working correctly

# Notes
- rumqttc w/ client certs: https://github.com/bytebeamio/rumqtt/blob/main/rumqttc/examples/tls2.rs
- Make sure to use rumqttc v5