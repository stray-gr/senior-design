import signal
import sys
from websockets.sync.client import connect


def hello():
    with connect("ws://localhost:8000/ws") as websocket:
        while True:
            message = websocket.recv()
            print(f"Received: {message}")


if __name__ == "__main__":
    signal.signal(signal.SIGINT, lambda s, f: sys.exit(0))
    print("Running ws client...")
    hello()