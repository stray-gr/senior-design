import aiomqtt
import asyncio
import signal
import sys

MQTT_HOST      = "localhost"
DATA_TOPIC     = "data"   # PUB
TIMER_TOPIC    = "timer"  # SUB

async def pub(client: aiomqtt.Client) -> None:
    await client.publish(DATA_TOPIC, payload="Empty Data")

async def main():
    async with aiomqtt.Client(MQTT_HOST) as client:
        await client.subscribe(TIMER_TOPIC)
        async with client.messages() as messages:
            async for msg in messages:
                print(msg.payload)
                await pub(client)

if __name__ == "__main__":
    signal.signal(signal.SIGINT, lambda s, f: sys.exit(0))
    print("Running client...")
    asyncio.run(main())