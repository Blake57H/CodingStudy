import asyncio
import hashlib
import time
end = 1000000

async def online_sha256(stream) -> bytes:
    hasher = hashlib.sha256()
    async for chunk in stream:
        # print(f"got chunk {chunk}")
        hasher.update(chunk)
    return hasher.digest()

if __name__ == '__main__':
    start = time.time()
    with open(r"C:\Users\tingt\Downloads\02_NotoSansCJK-TTF-VF.zip", 'rb') as stream:
        
    print(f"with async: {time.time() - start} seconds")

    start = time.time()
    loop(end)
    print(f"without async: {time.time() - start} seconds")
        