# Table of Contents
1. [Prerequisites](#prerequisites)
2. [Dockerfile Explanation](#dockerfile-explanation)
3. [Docker Container Creation](#docker-container-creation)
4. [Automation Script Reference](#automation-script-reference)
5. [RabbitMQ User Creation](#rabbitmq-user-creation)
6. [MQTTX Pub/Sub](#mqttx-pubsub)

# Prerequisites
Make sure to have the following software installed:
- Rancher Desktop 
- MQTTX CLI Tool (install via WSL2 if on Windows)
- tcpdump (install via WSL2 if on Windows)

# Dockerfile Explanation
Here's a step-by-step explanation of the RabbitMQ Broker's Dockerfile configuration:
1. Load the standard RabbitMQ docker image enable the MQTT plugin.
    ```Dockerfile
    FROM rabbitmq:4

    RUN rabbitmq-plugins enable --offline rabbitmq_mqtt
    ```
2. Copy the certificate authority's cert, along with the server's public key (crt), private key, and configuration file (conf) into the Docker image's file system.
    ```Dockerfile
    COPY certs/ca.crt /certs/ca.crt
    COPY certs/server.crt /certs/server.crt
    COPY certs/server.key /certs/server.key
    COPY rabbitmq.conf /etc/rabbitmq/rabbitmq.conf
    ```
3. Copy each [automation script](#automation-script-reference) into the Docker image's file system and prep them for execution via `chmod`.
    ```Dockerfile
    COPY scripts/ /scripts/
    RUN chmod -R +x /scripts/
    ```
4. Set the Docker image's entrypoint [init.sh](./scripts/init.sh).
    ```Dockerfile
    CMD [ "/scripts/init.sh" ]
    ```

# Docker Container Creation
First, create the certificate authority's cert and private key:
1. Create the CA private key: `openssl genrsa -des3 -out ca.key 2048`
2. Create the CA cert: `openssl req -new -x509 -days 360 -key ca.key -out ca.crt`

Next, create a public/private key pair for the server to use via TLS:
1. Create server private key: `openssl genrsa -out server.key 2048`
2. Create and sign a certificate request using the server's private key: `openssl req -new -out server.csr -key server.key`
    > Make sure to set **Common Name** to the message broker's hostname. In this case, *localhost* was used for development purposes
3. Using a CA cert and key, create the server's public key: `openssl x509 -req -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out server.crt -days 180`

Then, move the previously generated certs and keys into a *certs* folder before running the following command. This command will create a Docker image called *broker*: 
```bash
docker build -t broker .
```

Finally, run the following command to mount and start a Docker container using the previously create *broker* image:
```bash
docker run --rm --hostname localhost -p 8883:8883 -it broker
```

# Automation Script Reference
Here's a brief description of each automation script used by the Docker image:
- [users.sh](./scripts/users.sh) creates each RabbitMQ user and their password
- [perms.sh](./scripts/perms.sh) sets the topic configure, write, and read permissions of each user
- [init.sh](./scripts/init.sh) waits for the RabbitMQ server to start before running the *users* and *perms* scripts. This is done be waiting for RabbitMQ to create a PID file

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