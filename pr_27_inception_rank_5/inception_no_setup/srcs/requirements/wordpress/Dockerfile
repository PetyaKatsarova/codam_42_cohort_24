FROM alpine:3.16

RUN apk update && apk add --no-cache \
    php8-fpm \
    php8-mysqli \
    php8-curl \
    php8-gd \
    php8-json \
    php8-xml \
    php8-mbstring \
    php8-openssl \
    netcat-openbsd \
    curl

RUN mkdir -p /run/php /var/www/html && \
    addgroup -g 82 -S www-data 2>/dev/null || true && \
    adduser -u 82 -S www-data -G www-data 2>/dev/null || true && \
    chown -R www-data:www-data /var/www/html /run/php

WORKDIR /var/www/html

COPY ./conf/php-fpm.conf /etc/php8/php-fpm.d/www.conf
COPY ./tools/entrypoint.sh /entrypoint.sh

RUN chmod +x /entrypoint.sh

EXPOSE 9000

ENTRYPOINT ["/entrypoint.sh"]