#!/bin/sh

# this is inside the container, entrypoint.sh is exec when the container starts
# When you use Docker volumes in your docker-compose.yml, the /var/lib/mysql/ directory inside the container is mapped to a folder on your host machine. But the entrypoint script only sees the container's internal filesystem.
if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo "Initializing MariaDB..."
    mysql_install_db --user=mysql --datadir=/var/lib/mysql
fi

mysqld_safe --no-defaults --bind-address=0.0.0.0 &
MARIADB_PID=$!

sleep 5

# Read password from secret file
DB_PASSWORD=$(cat /run/secrets/db_password)

mysql -u root -e "CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;"
mysql -u root -e "CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${DB_PASSWORD}';"
mysql -u root -e "GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';"
mysql -u root -e "FLUSH PRIVILEGES;"


wait $MARIADB_PID
