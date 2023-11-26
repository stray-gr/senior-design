import aiomqtt
import asyncio
from blacksheep.server.controllers import Controller
from blacksheep import WebSocket, ws
from src.common import MqttData


MQTT_HOST  = "localhost"
DATA_TOPIC = "data"  # MQTT Topic SUB
DEV_DATA   = dict()  # Keeps track of current mqtt data for each device
DEV_DATA_LOCK = asyncio.Lock()  # Used to mediate access to device data
BROADCAST_INTERVAL = 2  # Sets broadcast interval to 2s


class ControlPanel(Controller):
    @ws("/ws")
    async def broadcast(self, websocket: WebSocket):
        data = '<div id="broadcast">Empty!</div>'
        await websocket.accept()
        try:
            while True:
                await DEV_DATA_LOCK.acquire()
                if len(DEV_DATA) != 0:
                    # TODO: replace with templating via self.view -> /views/control_panel/broadcast.jinja
                    data = '<div id="broadcast">'
                    for item in DEV_DATA:
                        data += f'<div>Hello</div>'
                    data += '</div>'
                DEV_DATA_LOCK.release()
                await websocket.send_text(data)
                await asyncio.sleep(BROADCAST_INTERVAL)
        except Exception as err:
            print(err)


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