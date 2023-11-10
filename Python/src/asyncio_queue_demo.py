import asyncio

# This queue allows coroutines 1 and 2 to share info with each other
Q = asyncio.Queue()

# Coroutine 1
async def disp() -> None:
    while not Q.empty():
        print(f'New data: {Q.get_nowait()}')
    print("Empty")

# Coroutine 2
async def get() -> None:
    data = 'yes'
    for _ in range(10):
        Q.put_nowait(data)
        data += 'yes'

async def main():
    asyncio.gather(get(), disp())

asyncio.run(main())
