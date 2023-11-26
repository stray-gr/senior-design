import aiomqtt
import argparse
import asyncio
import signal
import sys
import time
from domain.common import (
    MqttData, 
    MQTT_HOST, 
    MQTT_DATA_TOPIC, 
    MQTT_LWT_TOPIC,
    MQTT_TIMER_TOPIC
)
from random import uniform

# Run using: python -m mqtt.test_client <uuid>

HOST, PORT = MQTT_HOST

async def pub(client: aiomqtt.Client) -> None:
    data = MqttData(
        client.id, 
        time.time_ns(),
        uniform(0, 100), 
        uniform(0, 100), 
        uniform(0, 100)
    )
    await client.publish(MQTT_DATA_TOPIC, data.to_json())

async def main(uuid):
    lwt = aiomqtt.Will(MQTT_LWT_TOPIC, uuid)
    async with aiomqtt.Client(HOST, client_id=uuid, port=PORT, will=lwt) as client:
        await client.subscribe(MQTT_TIMER_TOPIC)
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