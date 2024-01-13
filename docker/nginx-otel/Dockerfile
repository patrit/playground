FROM nginx:1.25.3-alpine3.18

ADD nginx_signing.rsa.pub /etc/apk/keys/
RUN echo "http://nginx.org/packages/mainline/alpine/v3.18/main" >> /etc/apk/repositories
RUN apk add --no-cache nginx-module-otel
RUN echo "load_module modules/ngx_otel_module.so;" > a && \
    cat /etc/nginx/nginx.conf >> a && \
    mv a /etc/nginx/nginx.conf
ADD default.conf.template /etc/nginx/templates/