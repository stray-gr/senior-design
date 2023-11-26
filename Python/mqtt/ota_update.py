import aiomqtt
import asyncio
import glob
import jwt
import os
from domain.common import MQTT_HOST, MQTT_UPDATE_TOPIC
from domain.hidden import OTA_UPDATE_KEY

# Run using: python -m src.mqtt.ota_update

HOST, PORT = MQTT_HOST
EXCLUDED_FILES = {'example_hidden.py'}
BOARD_DIR  = 'board/'

async def main():
    os.chdir(BOARD_DIR)

    file_paths = []
    for item in glob.glob('./**', recursive=True):
        if os.path.isfile(item) and os.path.basename(item) not in EXCLUDED_FILES:
            print(f'Found {item}')
            file_paths.append(item)

    file_contents = dict()
    for fpath in file_paths:
        with open(fpath, 'r') as f:
            file_contents[fpath] = f.read()

    update = jwt.encode(file_contents, OTA_UPDATE_KEY, algorithm='HS256')
    async with aiomqtt.Client(HOST, port=PORT) as client:
        await client.publish(MQTT_UPDATE_TOPIC, update)

if __name__ == '__main__':
    asyncio.run(main())