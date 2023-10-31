import asyncio
import aiomqtt
import signal
import sys

MQTT_HOST      = "localhost"
DATA_TOPIC     = "data"   # SUB
TIMER_TOPIC    = "timer"  # PUB
TIMER_INTERVAL = 1 

async def sub(client: aiomqtt.Client) -> None:
    await client.subscribe(DATA_TOPIC)
    async with client.messages() as messages:
        async for msg in messages:
            print(msg.payload)

async def pub(client: aiomqtt.Client) -> None:
    while True:
        await client.publish(TIMER_TOPIC, payload=0)
        await asyncio.sleep(TIMER_INTERVAL)

async def main():
    async with aiomqtt.Client(MQTT_HOST) as client:
        await asyncio.gather(sub(client), pub(client))

if __name__ == "__main__":
    signal.signal(signal.SIGINT, lambda s, f: sys.exit(0))
    print("Running server...")
    asyncio.run(main())