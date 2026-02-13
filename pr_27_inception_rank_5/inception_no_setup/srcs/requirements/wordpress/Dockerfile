FROM alpine:3.21

RUN apk update && apk add --no-cache \
    php83 \
    php83-fpm \
    php83-mysqli \
    php83-curl \
    php83-gd \
    php83-json \
    php83-xml \
    php83-mbstring \
    php83-openssl \
    php83-phar \
    netcat-openbsd \
    curl

RUN mkdir -p /run/php /var/www/html && \
    addgroup -g 82 -S www-data 2>/dev/null || true && \
    adduser -u 82 -S www-data -G www-data 2>/dev/null || true && \
    chown -R www-data:www-data /var/www/html /run/php

# Install WP-CLI
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
    chmod +x wp-cli.phar && \
    mv wp-cli.phar /usr/local/bin/wp

WORKDIR /var/www/html

COPY ./conf/php-fpm.conf /etc/php83/php-fpm.d/www.conf
COPY ./tools/entrypoint.sh /entrypoint.sh

RUN chmod +x /entrypoint.sh

EXPOSE 9000

ENTRYPOINT ["/entrypoint.sh"]