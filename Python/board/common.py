import json

# MQTT DATA TOPIC
# PUB: board.main, mqtt.test_client
# SUB: app.controllers.control_panel, mqtt.server

# MQTT TIMER TOPIC
# PUB: mqtt.server
# SUB: board.main, mqtt.test_client

# MQTT UPDATE TOPIC
# PUB: mqtt.ota_update
# SUB: board.main

# NOTE: Each copy of common is independent of one another. 
# This is because MicroPython doesn't support dataclasses

MQTT_HOST         = ('192.168.1.162', 4000)
MQTT_DATA_TOPIC   = 'data'
MQTT_LWT_TOPIC    = 'lwt'
MQTT_TIMER_TOPIC  = 'timer'
MQTT_UPDATE_TOPIC = 'update'

class MqttData:
    def __init__(self, uuid: bytes, epoch: int, temp: float, humidity: float, power) -> None:
        self.data_dict = {
            'uuid': uuid,
            'epoch': epoch,
            'temp': temp,
            'humidity': humidity,
            'power': power
        }
    
    def to_json(self) -> str:
        return json.dumps(self.data_dict)