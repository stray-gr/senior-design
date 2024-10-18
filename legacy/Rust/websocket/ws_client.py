from websockets.sync.client import connect

def hello():
    with connect("ws://localhost:8080/ws") as websocket:
        for _ in range(12):
            message = websocket.recv()
            print(f"Received: {message}")

hello()