from starlette.requests import Request
from starlette.applications import Starlette
from starlette.routing import Route
from starlette.responses import PlainTextResponse, Response
import hashlib

async def online_sha256(stream) -> bytes:
    hasher = hashlib.sha256()
    async for chunk in stream:
        # print(f"got chunk {chunk}")
        hasher.update(chunk)
    return hasher.digest()

async def online_sha256_unasync(stream) -> bytes:
    hasher = hashlib.sha256()
    for chunk in stream:  # <-- will crash
        # print(f"got chunk {chunk}")
        hasher.update(chunk)
    return hasher.digest()

async def compute_sha256_async(request: Request) -> Response:
    print("got new connection")
    bytes_hash = await online_sha256(request.stream())
    return PlainTextResponse(bytes_hash)

async def compute_sha256_unasync(request: Request) -> Response:
    print("got new connection")
    bytes_hash = await online_sha256_unasync(request.stream())
    return PlainTextResponse(bytes_hash)
    
routes = [
    Route(path='/async', endpoint=compute_sha256_async, methods=['POST']),
    Route(path='/unasync', endpoint=compute_sha256_unasync, methods=['POST']),
]

app = Starlette(debug=True, routes=routes)

async def main_async():
    pass

def main():
    import uvicorn
    uvicorn.run(app, port=8080, log_level="info")
    
if __name__ == "__main__":
    main()

