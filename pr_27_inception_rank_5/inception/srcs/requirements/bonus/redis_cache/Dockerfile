FROM alpine:3.21

RUN apk add --no-cache redis

RUN mkdir -p /var/log/redis /data && \
    chown -R redis:redis /var/log/redis /data

COPY conf/redis.conf /etc/redis/redis.conf
RUN chown redis:redis /etc/redis/redis.conf

COPY tools/setup.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/setup.sh

EXPOSE 6379

HEALTHCHECK --interval=30s --timeout=3s --start-period=5s --retries=3 \
    CMD redis-cli ping || exit 1

USER redis

ENTRYPOINT ["/usr/local/bin/setup.sh"]