# build image
FROM golang:1.9.1-alpine as go_builder

ENV CGO_ENABLED=0
COPY webdav.go webdav.go
RUN apk update && apk add git
RUN go get golang.org/x/net/webdav
RUN go build -ldflags="-w -s" webdav.go

# final image
FROM alpine

COPY --from=go_builder /go/webdav /app/webdav

ENTRYPOINT ["/app/webdav"]
