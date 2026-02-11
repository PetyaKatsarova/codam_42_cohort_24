Docker Image = Blueprint for containers

Image: Packaged application with everything inside (code, libraries, OS, config)
Container: Running copy of an image
Writing a Docker Image = Creating one with a Dockerfile

Dockerfile = Instructions to build an image
FROM alpine:3.16
RUN apk add mysql
COPY entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]