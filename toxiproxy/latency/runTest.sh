#!/bin/bash

set -e

runTest() {
  echo -n "$1"
  docker run --rm --network=latency_default ab_image ab -n 100 http://web:5000/ | sed -n "s/Total:      //p"
}

configToxiProxy() {
  # values in ms
  curl -s -H "Content-Type: application/json" -X POST -d @populate.json http://127.0.0.1:8474/populate > /dev/null
  curl -s -H "Content-Type: application/json" -X POST -d '{"type":"latency", "toxicity":1, "attributes":{"latency":'$1',"jitter":'$2'}}' http://127.0.0.1:8474/proxies/redis_proxy/toxics > /dev/null
}

docker-compose build
docker-compose up -d

echo "build test image ..."
docker build -t ab_image -f Dockerfile.test .

echo ""
echo "Running tests ..."
echo ""
echo "                       min  mean[+/-sd] median   max"
configToxiProxy 0 0
runTest "Bare:                "
configToxiProxy 10 0
runTest "latency=10:          "
configToxiProxy 30 0
runTest "latency=30:          "
configToxiProxy 30 10
runTest "latency/jitter=30/10:"
configToxiProxy 30 30
runTest "latency/jitter=30/30:"
echo ""
echo ""

docker-compose down
