# BUILDER
FROM ubuntu:19.10 as builder

RUN apt-get update && apt-get install -y --no-install-recommends git cmake ca-certificates make g++ libpoco-dev

RUN git clone https://github.com/census-instrumentation/opencensus-cpp.git

WORKDIR opencensus-cpp
ENV CXXFLAGS --std=c++17 -O2
RUN env
RUN cmake -H. -B.build
RUN cmake --build .build -- -j4
RUN (cd .build && ctest --output-on-failure)

WORKDIR /app
COPY . .
RUN make

# RUNTIME
#RUN apt-get update && \
#    apt-get install -y --no-install-recommends \
#    libpoconet62 libpocofoundation62 libpocoutil62 && \
#    rm -rf /var/lib/apt/lists/*
#WORKDIR /app
#COPY --from=builder /app/server .
