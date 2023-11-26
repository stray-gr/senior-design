import json
from dataclasses import asdict, dataclass, fields

@dataclass
class MqttData:
    uuid: str | int  # Unique user ID
    epoch: int       # Unix epoch in ns
    temp: float      # Temperature in F
    humidity: float  # Relative humidity
    power: float     # Battery level percentage

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
        


