#!/bin/bash

sudo perf record -e sched:sched_process_exec -e sched:sched_process_exit -a -- $@

data=$(sudo perf script | \
sed -E 's/[ ]*(.*)[ ]+([0-9]+)[ ]+\[[0]*([0-9]+)\][ ]+([^:]*):.*(sched_process_[^:]*).*/\
{"name": "\1", "cat": "process", "ph": "\5", "ts": \4, "pid": \3, "tid": \2},/g' | \
sed "s/sched_process_exec/B/g" | sed "s/sched_process_exit/E/g")

echo "["${data:0:-1}"]" > tracecmd.json
