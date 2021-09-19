from dataclasses import dataclass
from fastapi import FastAPI
from kubernetes import client, config, watch
from typing import Dict, List
import threading

@dataclass
class RouteItem:
    namespace: str
    host: str
    path: str
    openapi_ui: List[str]

ROUTES: Dict[str, RouteItem] = {}

def track_ingress() -> None:
    crd = client.CustomObjectsApi()
    w = watch.Watch()
    for event in w.stream(crd.list_cluster_custom_object, "route.openshift.io", "v1",  "routes"):
        metadata = event["object"]["metadata"]
        uid = metadata["uid"]
        if event['type'] == "DELETED":
            ROUTES.pop(uid, None)
            continue
        annotations = metadata.get("annotations", {})
        namespace = metadata["namespace"]
        spec = event["object"]["spec"]
        openapi_ui =  [v for k, v in annotations.items() if k.startswith("openapi.ui")]
        if openapi_ui:
            ROUTES.update({uid: RouteItem(namespace, spec["host"], spec["path"], openapi_ui)})

config.load_kube_config()
kubethread = threading.Thread(target = track_ingress)
kubethread.start() 

app = FastAPI()

@app.get("/healthz")
async def healthz() -> Dict[str, str]:
    return {}

@app.get("/api/openapi")
async def list_openapi() -> List[RouteItem]:
    return list(ROUTES.values())
