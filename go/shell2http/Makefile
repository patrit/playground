all:
	docker build -t shell2http .
test: all
	docker run -d --name=shell2httptest -p 8888:80 shell2http
	curl localhost:8888/cpuinfo.json | head -n 10
	curl localhost:8888/ | head -n 10
	docker stop shell2httptest
	docker rm shell2httptest
