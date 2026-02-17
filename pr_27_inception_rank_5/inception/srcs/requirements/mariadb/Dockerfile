FROM alpine:3.21

RUN apk update && apk add --no-cache \
    mariadb \
    mariadb-client

RUN mkdir -p /run/mysqld && \
    chown -R mysql:mysql /run/mysqld

EXPOSE 5306

COPY ./conf/mariadb.cnf /etc/mysql/my.cnf
RUN chmod 644 /etc/mysql/my.cnf
COPY ./tools/entrypoint.sh /entrypoint.sh

RUN chmod +x /entrypoint.sh

ENTRYPOINT ["/entrypoint.sh"]
