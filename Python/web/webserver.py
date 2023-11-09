from quart import (
    Blueprint, Quart, 
    abort, make_response, render_template, 
    request, websocket
)
import aiomqtt
import asyncio

MQTT_HOST  = "localhost"
DATA_TOPIC = "data"  # MQTT Topic SUB
DATA_LST   = []      # Keeps track of current data
DATA_LST_LOCK = asyncio.Lock()  # Used to mediate access to the data list
BROADCAST_INTERVAL = 2

app = Quart(__name__)  # INIT Quart App

# Gives static file access via /static/filename.ext
static_files = Blueprint('static', __name__, url_prefix='/static')
app.register_blueprint(static_files)

# Background task that checks the data MQTT topic for new messages
async def monitor_mqtt():
    async with aiomqtt.Client(MQTT_HOST) as client:
        await client.subscribe(DATA_TOPIC)
        async with client.messages() as messages:
            async for msg in messages:
                # Appends new data to the data list once the lock is acquired
                await DATA_LST_LOCK.acquire()
                DATA_LST.append(msg.payload)
                DATA_LST_LOCK.release()


# SSE, which requires HTTP/2
@app.route("/sse")
async def sse():
    if "text/event-stream" not in request.accept_mimetypes:
        abort(400)

    async def send_events():
        while True:
            data  = "<div>Empty!</div>"

            await DATA_LST_LOCK.acquire()
            if DATA_LST != []:
                data = ""
                for item in DATA_LST: 
                    data += f"<div>{item.decode('utf-8', 'replace')}</div>" 
            DATA_LST_LOCK.release()

            message = f"data: {data}\nevent: update\n\n".encode()
            yield message
            await asyncio.sleep(BROADCAST_INTERVAL)

    response = await make_response(
        send_events(),
        {
            'Content-Type': 'text/event-stream',
            'Cache-Control': 'no-cache',
            'Transfer-Encoding': 'chunked',
        },
    )
    return response


# Broadcast socket. Note that WebSockets are lower latency and are more resource efficient
# than SSEs. Therefore, this may be more optimal for a Python app
@app.websocket('/ws')
async def ws():
    data  = '<div id="broadcast">Empty!</div>'
    while True:
        await DATA_LST_LOCK.acquire()
        if DATA_LST != []:
            data = '<div id="broadcast">'
            for item in DATA_LST:
                data += f'<div>{item.decode("utf-8", "replace")}</div>'
            data += '</div>'
        DATA_LST_LOCK.release()

        await websocket.send(data)
        await asyncio.sleep(BROADCAST_INTERVAL)


@app.route('/')
async def index():
    return await render_template('index.html')


@app.before_serving
async def startup():
    app.add_background_task(monitor_mqtt)


app.run()