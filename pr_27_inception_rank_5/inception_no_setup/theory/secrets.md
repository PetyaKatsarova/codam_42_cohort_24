.env files — storing environment variables

Purpose: Store variables like database name, usernames, ports outside your Dockerfiles.

Rules for Inception:

Must use a .env file.

No passwords should go here (use secrets for passwords).

Can store non-sensitive info: DB name, DB user, ports, WordPress config.
Make sure .env is not committed with secrets (it’s safe for non-confidential info).
--------------------------------
Docker secrets — storing confidential info

Purpose: Store sensitive info like passwords, API keys, root credentials securely.

Secrets are mounted inside the container, never baked into Docker images.

Create secrets
echo "rootpassword123" | docker secret create db_root_password -
echo "userpassword123" | docker secret create db_password -
This stores the passwords securely in Docker swarm.

Step 2: Reference secrets in docker-compose.yml
services:
  mariadb:
    image: mariadb:11
    container_name: mariadb
    env_file:
      - .env
    environment:
      MYSQL_DATABASE: ${MYSQL_DATABASE}        # from .env
      MYSQL_USER: ${MYSQL_USER}                # from .env
      MYSQL_PASSWORD_FILE: /run/secrets/db_password
      MYSQL_ROOT_PASSWORD_FILE: /run/secrets/db_root_password
    secrets:
      - db_password
      - db_root_password

    wordpress:
    image: wordpress:6.4-php8.3-fpm
    env_file:
      - .env
    environment:
      WORDPRESS_DB_NAME: ${MYSQL_DATABASE}       # from .env
      WORDPRESS_DB_USER: ${MYSQL_USER}          # from .env
      WORDPRESS_DB_PASSWORD_FILE: /run/secrets/db_password

secrets:
  db_password:
    external: true
  db_root_password:
    external: true


MYSQL_PASSWORD_FILE points to the secret inside the container (/run/secrets/...).

The container reads it at runtime, never stored in image.

Do not write secrets in .env or Dockerfile.

Using secrets inside entrypoint scripts

Read the secret inside your entrypoint.sh:
#!/bin/sh
set -e

# Read secret
DB_PASSWORD=$(cat /run/secrets/db_password)
DB_ROOT_PASSWORD=$(cat /run/secrets/db_root_password)

# Use them to initialize MariaDB
mysql -u root -p"$DB_ROOT_PASSWORD" -e "CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;"
mysql -u root -p"$DB_ROOT_PASSWORD" -e "CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${DB_PASSWORD}';"
mysql -u root -p"$DB_ROOT_PASSWORD" -e "GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';"
mysql -u root -p"$DB_ROOT_PASSWORD" -e "FLUSH PRIVILEGES;"
