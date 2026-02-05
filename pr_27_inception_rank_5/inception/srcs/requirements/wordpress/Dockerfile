FROM alpine:3.16

RUN apk update && apk add --no-cache \
    php-fpm \
    php-mysqli \
    netcat-openbsd

RUN mkdir -p /run/php /var/www/html

WORKDIR /var/www/html

COPY ./conf/php-fpm.conf /etc/php/php-fpm.d/www.conf
COPY ./tools/entrypoint.sh /entrypoint.sh

RUN chmod +x /entrypoint.sh

EXPOSE 9000

ENTRYPOINT ["/entrypoint.sh"]
