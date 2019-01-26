#!/bin/bash

delay=$(echo $QUERY_STRING | tr '&' '\n' | grep delay | cut -d'=' -f2)
[ -z "$delay" ] && delay=0.5

for ((COUNT = 1; COUNT <= 1000; COUNT++)); do
  cat /proc/cpuinfo | sed -e ':a' -e 'N' -e '$!ba' -e "s#\n#<br/>#g"
  sleep $delay
done
