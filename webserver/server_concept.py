import asyncio
import websockets

CONNECTIONS = set()

async def register(websocket):
    CONNECTIONS.add(websocket)
    try:
        await websocket.wait_closed()
    finally:
        CONNECTIONS.remove(websocket)

async def yell():
    THINGS = ["Joe", "Beanolozi", "Lemme", "Tell", "Ya", "HWhat"]
    idx = 0
    while True:
        msg = f"""
            <div id="target" hx-swap-oob="true">
                {THINGS[idx]}
            </div>
        """
        idx = (idx + 1) % len(THINGS)
        websockets.broadcast(CONNECTIONS, msg)
        await asyncio.sleep(2)

async def main():
    async with websockets.serve(register, "localhost", 5678):
        await yell()

if __name__ == "__main__":
    asyncio.run(main())
