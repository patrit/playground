#!/usr/bin/env python3

from flask import Flask
import redis
import json

import logging
log = logging.getLogger('werkzeug')
log.setLevel(logging.ERROR)

# start redis with
# docker run -p 6379:6379 --rm redis:5.0.5-alpine3.10

app = Flask(__name__)
app.debug = False
db = redis.Redis('localhost') #connect to server

@app.route('/keys', methods = ['GET'])
def all_keys():
    return json.dumps([x.decode("utf-8") for x in db.keys("*")]), 200

@app.route('/key/<key>', methods = ['GET'])
def get_key(key):
    return json.dumps(db.get(key).decode("utf-8")), 200

@app.route('/list/<key>', methods = ['GET'])
def get_list(key):
    return json.dumps([x.decode("utf-8") for x in db.lrange(key, 0, -1)]), 200

if __name__ == "__main__":
    for i in range(100000):
        db.delete(f"key{i}")
        db.delete(f"list{i}")
        lst = [f"value_{i}_{j}" for j in range(20)]
        db.set(f"key{i}", lst)
        db.lpush(f"list{i}", *lst)
    app.run()
