import aiomqtt
import argparse
import asyncio
import signal
import sys
import time
from random import uniform
from src.common import MqttData

# Run using: python -m src.mqtt.client <uuid>

MQTT_HOST      = "localhost"
DATA_TOPIC     = "data"   # PUB
TIMER_TOPIC    = "timer"  # SUB

async def pub(client: aiomqtt.Client) -> None:
    data = MqttData(
        client.id, 
        time.time_ns(),
        uniform(0, 100), 
        uniform(0, 100), 
        uniform(0, 100)
    )
    await client.publish(DATA_TOPIC, data.to_json())

async def main(uuid):
    async with aiomqtt.Client(MQTT_HOST, client_id=uuid) as client:
        await client.subscribe(TIMER_TOPIC)
        async with client.messages() as messages:
            async for msg in messages:
                print(msg.payload)
                await pub(client)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Test MQTT Client')
    parser.add_argument('uuid', type=str, help='Unique User ID')
    args = parser.parse_args()
    uuid = args.uuid

    print(f"Running client w/ username = {uuid}")
    signal.signal(signal.SIGINT, lambda s, f: sys.exit(0))
    asyncio.run(main(uuid))