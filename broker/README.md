# Instructions
### Docker Build
```bash
docker build -t broker .
docker run --rm --hostname test-broker -p 1883:1883 broker
```

### MQTT Pub/Sub
```bash
mqttx sub -t 'pulse' -h 'localhost' -p 1883 -V 3.1
mqttx pub -t 'pulse' -h 'localhost' -p 1883 -V 3.1 -m "hello there"
```

# Notes
- MQTT and AMQP topics will have to be declared at runtime
- The `mqttx` tool was installed to Ubuntu 24.04 WSL