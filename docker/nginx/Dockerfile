FROM alpine:3.10 as builder

ENV NGINX_VERSION nginx-1.17.6
ENV NGINX_SHA512 "8ad6c3d066bf51f3fde3454bb93f2eeab0412d1c10eac0841fd50ec25b0f1204c85f15cb950c6bbe128c0ff72efe5b0bb804b5d66a8bf6234e0e4776aa67b9eb"

RUN apk upgrade \
    && apk --no-cache --upgrade add openssl-dev zlib-dev pcre-dev wget build-base
WORKDIR /tmp/src
RUN echo "${NGINX_SHA512}  ${NGINX_VERSION}.tar.gz" > ${NGINX_VERSION}.tar.gz.sha512
RUN wget -q http://nginx.org/download/${NGINX_VERSION}.tar.gz && \
    sha512sum -c ${NGINX_VERSION}.tar.gz.sha512 && \
    tar -zxvf ${NGINX_VERSION}.tar.gz
WORKDIR /tmp/src/${NGINX_VERSION}
RUN ./configure \
    --with-http_ssl_module \
    --with-http_gzip_static_module \
    --prefix=/etc/nginx \
    --conf-path=/etc/nginx/nginx.conf \
    --http-log-path=/var/log/nginx/access.log \
    --error-log-path=/var/log/nginx/error.log \
    --sbin-path=/usr/sbin/nginx \
    --with-http_sub_module
RUN make install
RUN strip /usr/sbin/nginx


FROM alpine:3.10
COPY --from=builder /usr/sbin/nginx /usr/sbin/nginx
COPY --from=builder /etc/nginx/mime.types /etc/nginx/mime.types

# Bring in tzdata so users could set the timezones through the environment
# variables
RUN apk upgrade \
    && apk add --no-cache --upgrade tzdata openssl pcre \
    # forward request and error logs to docker log collector
    && mkdir -p /var/log/nginx/ \
    && ln -sf /dev/stdout /var/log/nginx/access.log \
    && ln -sf /dev/stderr /var/log/nginx/error.log

RUN mkdir -p  /usr/share/nginx/html
ADD nginx.conf /etc/nginx/
RUN chmod 777 /etc/nginx/nginx.conf \
    && chmod 777 /etc/nginx \
    && chmod 777 /var/run

RUN echo "foo" > /usr/share/nginx/html/foo.txt

# create nginx user/group first, to be consistent throughout docker variants
RUN addgroup -g 101 -S nginx \
    && adduser -S -D -H -u 101 -h /var/cache/nginx -s /sbin/nologin -G nginx -g nginx nginx 
USER nginx

EXPOSE 8080
STOPSIGNAL SIGTERM
CMD ["nginx"]