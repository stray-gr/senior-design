from websockets.sync.client import connect

def hello():
    with connect("ws://localhost:5000/ws") as websocket:
        while True:
            message = websocket.recv()
            print(f"Received: {message}")

hello()