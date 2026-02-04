1. ssh from terminal and run commdands: 

sudo apt update && sudo apt upgrade -y
sudo apt install -y docker.io docker-compose
sudo systemctl enable --now docker
sudo usermod -aG docker $USER

** install docker engine(docker.io) -y: without prompting
** docker-compose is a tool for defining and running multi-container Docker apps using a single YAML file (typically docker-compose.yml). It lets you start, stop, and manage related services together (e.g., database, backend, reverse proxy) with one command.
**  Adds user to the docker group so user can run Docker commands without sudo after re-login.
** systemctl enable --now docker: enables the Docker service to start automatically on boot and starts it immediately (--now) in the current session.

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


