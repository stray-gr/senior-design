# MQTTX Integration
Subscribe to the Data Topic:
```bash 
mqttx sub -h test.mosquitto.org -p 8883 -l mqtts -V 5 --ca src/ca.crt -t "6137cde4893c59f76f005a8123d8e8e6"
```

Publish to the Pulse Topic:
```bash 
mqttx pub -h test.mosquitto.org -p 8883 -l mqtts -V 5 --ca src/ca.crt -t "5d4ff171536e1f3c63afcf6709574876" -m ""
```

Note that the names of each topic had the MD5 hashing algorithm applied to them. That way, there's less chance of using a pre-existing topic

# TODO
- Update documentation for firmware and broker 
    - firmware uses Platform IO, ESP-IDF, and Wokwi-CLI
    - broker doesn't need mqttx at the moment
- Senior design slides and presentation
- Upgrade MQTT to V5