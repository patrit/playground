FROM alpine:3.16

RUN apk add --no-cache gnuplot font-misc-misc

WORKDIR /work
ENTRYPOINT ["/usr/bin/gnuplot"]
CMD ["--help"]
