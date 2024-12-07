import aiomqtt
import asyncio
from blacksheep import WebSocket, ws
from blacksheep.server.controllers import Controller
from blacksheep.server.responses import view
from domain.common import MqttData, MQTT_HOST, MQTT_DATA_TOPIC, MQTT_LWT_TOPIC


HOST, PORT = MQTT_HOST
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
                        raw_data = view('broadcast', {'dev_data_list': DEV_DATA.values()})
                        data = raw_data.content.body.decode('utf-8', 'replace')
                await websocket.send_text(data)
                await asyncio.sleep(BROADCAST_INTERVAL)
        except Exception as err:
            print(f'ERROR: {err}')


# Background task that checks the data MQTT topic for new messages
async def monitor_mqtt():
    async with aiomqtt.Client(HOST, port=PORT) as client:
        await client.subscribe(MQTT_DATA_TOPIC)
        await client.subscribe(MQTT_LWT_TOPIC)
        async with client.messages() as messages:
            async for msg in messages:
                topic = msg.topic.value
                if topic == MQTT_DATA_TOPIC:
                    try:
                        data = MqttData.try_load_msg(msg.payload)
                    except Exception as err:
                        print(f'ERROR: {err}')
                    else:
                        # Appends new data to the data list once the lock is acquired
                        async with DEV_DATA_LOCK:
                            DEV_DATA[data.uuid] = data
                elif topic == MQTT_LWT_TOPIC:
                    uuid = msg.payload.decode('utf-8', 'replace')
                    print(f'INFO: Clearing device data for {uuid}')
                    async with DEV_DATA_LOCK:
                        DEV_DATA.pop(uuid)
