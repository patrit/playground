# build image
FROM golang:1.9.1-alpine as go_builder

ENV CGO_ENABLED=0
COPY server.go server.go
RUN go build -ldflags="-w -s" server.go

# final image
FROM alpine

COPY --from=go_builder /go/server /app/server
COPY cpuinfo.sh /app/cpuinfo.sh
COPY env.sh /app/env.sh
COPY index.html /app/index.html

ENTRYPOINT ["/app/server"]
