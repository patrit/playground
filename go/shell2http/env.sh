#!/bin/sh

echo "{"
env | sed -E 's/([^=]*)=(.*)/"\1": "\2",/g'
echo -n '"DATE": "'
date | tr -d '\n'
echo '"'
echo "}"
