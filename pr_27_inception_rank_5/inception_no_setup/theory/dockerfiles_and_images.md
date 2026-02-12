FROM alpine:latest

Uses the latest Alpine Linux as the base image (a minimal, fast Linux distribution).
RUN apk update && apk add --no-cache ...

Updates Alpine’s package index and installs PHP 8.3 with required extensions and tools (like curl, netcat). --no-cache keeps the image small.

RUN mkdir -p /run/php /var/www/html ...

Creates necessary directories for PHP and your web files.
Adds a group and user called www-data (with ID 82), which is a common web server user.
Changes ownership of the created directories to www-data for security.




WORKDIR /var/www/html

Sets the working directory for the next instructions and for when the container runs.

EXPOSE 9000

Documents that the container will listen on port 9000 (for PHP-FPM).

** What is a Docker image? **
A Docker image is a snapshot of a filesystem and its configuration. It contains everything needed to run an application: code, runtime, libraries, environment variables, and config files. You use a Dockerfile to define how to build this image.
-------------------------------------
How do you build the image yourself?
You build the image using the docker build command. For example, if your Dockerfile is in the current directory:
docker build -t my-wordpress-image .

-t my-wordpress-image gives your image a name.
. means "build using the Dockerfile in this directory".
--------------------------------------
In a real project, you usually use docker-compose to build all images defined in your docker-compose.yml:docker-compose build This will look for Dockerfiles specified in the docker-compose.yml and build each image accordingly.
--------------------------------------
Your Dockerfile creates a custom image for your service.
You build it with docker build or docker-compose build.
A Docker image is a packaged environment for your app, created from your Dockerfile.
---------------------------------------
addgroup: Adds a new group to the system.
-g 82: Sets the group ID to 82 (standard for www-data).
-S: Creates a system group (not a regular user group).
www-data: The name of the group.
2>/dev/null: Hides any error messages (redirects stderr to null).
|| true: If the command fails (e.g., group already exists), it won’t stop the build; it just continues.

/var/www/html is the standard directory for web server files (used by Apache, Nginx, etc.).
----------------------------------------
docker-compose -f srcs/docker-compose.yml --env-file srcs/.env build will look for Dockerfile files in the build context specified for each service in your docker-compose.yml. It will then build the images using those Dockerfiles (from your own files), not from pre-built images. This is exactly what you want for your project requirements. example:
services:
  mariadb:
    image: mariadb
    build: ./requirements/mariadb
    container_name: mariadb
    env_file:
      - .env
-------------------------------------------
driver_opts:
  type: none
  o: bind
  device: /home/${USER}/data/mariadb
That is a bind mount disguised as a volume.
-------------------------------------------
** What does driver: local mean? **
Volume is stored on the local Docker host
Not using NFS
Not using external driver
Default Docker volume driver
-------------------------------------------
COMPOSE=docker-compose -p inception -f srcs/docker-compose.yml --env-file srcs/.env

Container names → inception_nginx
Volumes → inception_db
Networks → inception_default
Without -p, Docker uses the folder name.
---------------------------------------------

| Type   | Container Path                | Host Path / Volume                     | Notes                 |
| ------ | ----------------------------- | -------------------------------------- | --------------------- |
| volume | /var/lib/mysql                | inception_db (Docker volume)           | persistent DB storage |
| bind   | /run/secrets/db_password      | /home/.../secrets/db_password.txt      | read-only secret file |
| bind   | /run/secrets/db_root_password | /home/.../secrets/db_root_password.txt | read-only root secret |
