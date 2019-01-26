#!/bin/bash

if [ ! -e websocketd ]; then
  wget https://github.com/joewalnes/websocketd/releases/download/v0.3.0/websocketd-0.3.0-linux_amd64.zip
  unzip websocketd-0.3.0-linux_amd64.zip
fi

./websocketd --port=8088 --dir=.
