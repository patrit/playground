
build:
	emcc func.c -O2 -g4 -s ASM_JS="1" -s EXPORTED_FUNCTIONS="['_main', '_fib']" -o func.js

run: build
	python -m SimpleHTTPServer 9000
