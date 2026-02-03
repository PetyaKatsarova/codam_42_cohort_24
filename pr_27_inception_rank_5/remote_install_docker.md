1. ssh from terminal

2. from there:
sudo apt update && sudo apt upgrade -y

sudo apt install -y docker.io docker-compose
sudo systemctl enable --now docker
sudo usermod -aG docker $USER

Log out/in.

project structure in git:
Makefile
srcs/
  docker-compose.yml
  .env
  requirements/
    nginx/
    wordpress/
    mariadb/
    tools/

services setup, inside repo:
MariaDB: Dockerfile + init script (create DB/user)
WordPress: Dockerfile + wp-config + php-fpm
Nginx: Dockerfile + TLS + reverse proxy to WP
Volumes: for DB + WP
Network: internal docker network


