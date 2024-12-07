import json
from dataclasses import asdict, dataclass, fields

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


@dataclass
class MqttData:
    uuid: str | bytes  # Unique user ID
    epoch: int         # Unix epoch in ns
    temp: float        # Temperature in F
    humidity: float    # Relative humidity
    power: float       # Battery level percentage

    def to_dict(self) -> dict:
        return asdict(self)

    def to_json(self) -> str:
        return json.dumps(asdict(self))

    @classmethod
    def try_load_msg(cls, msg): 
        # Can raise JSONDecodeError or KeyError
        json_dict = json.loads(msg.decode('utf-8', 'replace'))  
        for f in fields(cls): 
            if f.name not in json_dict: 
                raise KeyError('Field missing in message data')
        return cls(
            json_dict['uuid'],
            json_dict['epoch'],
            json_dict['temp'],
            json_dict['humidity'],
            json_dict['power']
        )
        


