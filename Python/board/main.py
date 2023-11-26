import dht
import jwt
import machine
import time
import ubinascii
from common import (
    MqttData,
    MQTT_HOST, 
    MQTT_DATA_TOPIC, 
    MQTT_LWT_TOPIC,
    MQTT_TIMER_TOPIC, 
    MQTT_UPDATE_TOPIC
)
from hidden import OTA_UPDATE_KEY
from random import uniform
from umqtt.simple import MQTTClient

HOST, PORT = MQTT_HOST
UUID = ubinascii.hexlify(machine.unique_id())
client = MQTTClient(UUID, HOST, port=PORT)
temp_rh_sensor = dht.DHT22(machine.Pin(4))

def sub_cb(raw_topic: bytes, raw_msg: bytes):
    topic = raw_topic.decode('utf-8', 'replace')
    if topic == MQTT_TIMER_TOPIC:
        temp_rh_sensor.measure()
        data = MqttData(
            UUID,
            time.time_ns(),   # Time reporting is off
            temp_rh_sensor.temperature(),
            temp_rh_sensor.humidity(),
            uniform(0, 100)
        )
        client.publish(MQTT_DATA_TOPIC, data.to_json())
    elif topic == MQTT_UPDATE_TOPIC:
        msg = raw_msg.decode('utf-8', 'replace')
        try:
            update = jwt.decode(msg, OTA_UPDATE_KEY, algorithms=['HS256'])
        except Exception as err:
            print(f'UPDATE ERROR: {err}')
        else:
            print('JWT verified, installing update')
            for fpath, content in update.items():
                with open(fpath, 'w') as f:
                    f.write(content)
            machine.reset()


print(f'Running client w/ username = {UUID}')
# print('OTA WORKED')
client.set_callback(sub_cb)
client.set_last_will(MQTT_LWT_TOPIC, UUID)

client.connect()
client.subscribe(MQTT_TIMER_TOPIC)
client.subscribe(MQTT_UPDATE_TOPIC)

try:
    while True:
        client.wait_msg()
finally:
    # Handle reconnection here?
    client.disconnect()
