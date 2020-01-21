CXXFLAGS := --std=c++17 -O2  -I.
LDFLAGS=-O2 --std=c++17
LDLIBS=-lPocoNet -lPocoUtil -lPocoFoundation

OBJS=Server.o

all: server

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@ -I /opencensus-cpp/ -I /opencensus-cpp/.build/_deps/abseil-src/

server: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

clean:
	rm -f src/*.o server

format:
	clang-format -i Server.cpp

testab:
	ab -p download.json -T application/json -c 4 -n 100 http://localhost:8080/
