import asyncio
import httpx
from pathlib import Path
import time

async def fake_file_data():
    yield b"hellp, "
    await asyncio.sleep(0.2)
    yield b"world."
    yield b""
    
async def real_file_data():
    count = 0
    file_path = Path(
        r"C:\Users\tingt\Downloads\02_NotoSansCJK-TTF-VF.zip"
    )
    stream = open(file_path, 'rb')
    while True:
        chunk = stream.read(2048)
        if not chunk:
            break
        # print(f'sending chunk {count}')
        # count+=1
        yield chunk
    stream.close()
        

async def main():
    async with httpx.AsyncClient() as client:
        response = await client.post(
            "http://localhost:8080/async",
            data=real_file_data()
        )
        data = response.read()
        print("Got async response: ", data.hex())

    async with httpx.AsyncClient() as client:
        response = await client.post(
            "http://localhost:8080/unasync",
            data=real_file_data()
        )
        data = response.read()
        print("Got unasync response: ", data.hex())
        
if __name__ == "__main__":
    start = time.time()
    asyncio.run(main())
    print(f"elapsed {time.time() - start}")