import aiomqtt
import asyncio
from blacksheep import WebSocket, ws
from blacksheep.server.controllers import Controller
from blacksheep.server.responses import view
from domain.common import MqttData


MQTT_HOST  = "localhost"
DATA_TOPIC = "data"  # MQTT Topic SUB
DEV_DATA   = dict()  # Keeps track of current mqtt data for each device
DEV_DATA_LOCK = asyncio.Lock()  # Used to mediate access to device data
BROADCAST_INTERVAL = 2  # Sets broadcast interval to 2s


class ControlPanel(Controller):
    @ws("/ws")
    async def broadcast(self, websocket: WebSocket):
        data = '<div class="border" id="broadcast">Empty!</div>'
        try:
            await websocket.accept()
            while True:
                async with DEV_DATA_LOCK:
                    if len(DEV_DATA) != 0:
                        print('cool lol')
                        raw_data = view('broadcast', {'dev_data_list': DEV_DATA.values()})
                        data = raw_data.content.body.decode('utf-8', 'replace')
                await websocket.send_text(data)
                await asyncio.sleep(BROADCAST_INTERVAL)
        except Exception as err:
            print(f'ERROR: {err}')


# Background task that checks the data MQTT topic for new messages
async def monitor_mqtt():
    async with aiomqtt.Client(MQTT_HOST) as client:
        await client.subscribe(DATA_TOPIC)
        async with client.messages() as messages:
            async for msg in messages:
                try:
                    data = MqttData.try_load_msg(msg.payload)
                except Exception as err:
                    print(f'ERROR: {err}')
                else:
                    # Appends new data to the data list once the lock is acquired
                    await DEV_DATA_LOCK.acquire()
                    DEV_DATA[data.uuid] = data
                    DEV_DATA_LOCK.release()