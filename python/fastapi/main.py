import asyncio
from fastapi import FastAPI, Response
from typing import Dict, Tuple

app = FastAPI(
    title="Batch Rest API",
    description="An interface to start batches for single contract",
    version="0.0.1",
    contact={
        "name": "Deadend",
        "url": "http://dead.end",
        "email": "dude@dead.end",
    },
    license_info = {
        "name": "Apache 2.0",
        "url": "https://www.apache.org/licenses/LICENSE-2.0.html",
    },)

@app.get("/healthz")
async def healthz() -> dict[str, str]:
    return {}

@app.get("/task")
async def list_tasks() -> Response:
    out, err = await _exec_shell("./tkn task list", {})
    return Response(content=out, media_type="text/plain")

@app.get("/task/{taskname}")
async def start_task(taskname: str, LVIDEXT: int) -> Response:
    env = {"LVIDEXT": str(LVIDEXT)}
    out, err = await _exec_shell("env", env)
    return Response(content=out, media_type="text/plain")

async def _exec_shell(cmd: str, env: Dict[str, str]) -> Tuple[str, str]:
    proc = await asyncio.create_subprocess_exec("/bin/sh", "-c", cmd,
        stdout=asyncio.subprocess.PIPE,
        stderr=asyncio.subprocess.PIPE,
        env=env)
    stdout, stderr = await proc.communicate()
    if proc.returncode:
        raise Exception(stderr, proc.returncode)
    return stdout.decode().strip(), stderr.decode().strip()
