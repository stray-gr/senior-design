import asyncio
import aiomqtt
import signal
import sys
from domain.common import MqttData, MQTT_HOST, MQTT_DATA_TOPIC, MQTT_TIMER_TOPIC

# Run using: python -m src.mqtt.server

HOST, PORT = MQTT_HOST
TIMER_INTERVAL = 1 

async def sub(client: aiomqtt.Client) -> None:
    await client.subscribe(MQTT_DATA_TOPIC)
    async with client.messages() as messages:
        async for msg in messages:
            try:
                data = MqttData.try_load_msg(msg.payload)
            except Exception as err:
                print(f'ERROR: {err}')
            else:
                print(data)

async def pub(client: aiomqtt.Client) -> None:
    while True:
        await client.publish(MQTT_TIMER_TOPIC, payload=0)
        await asyncio.sleep(TIMER_INTERVAL)

async def main():
    async with aiomqtt.Client(HOST, port=PORT) as client:
        await asyncio.gather(sub(client), pub(client))

if __name__ == "__main__":
    signal.signal(signal.SIGINT, lambda s, f: sys.exit(0))
    print("Running server...")
    asyncio.run(main())