#!/bin/sh
set -e

echo "[MariaDB] Starting initialization..."

# Read secrets
DB_PASSWORD=$(cat /run/secrets/db_password)
DB_ROOT_PASSWORD=$(cat /run/secrets/db_root_password)

# Initialize if needed
if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo "[MariaDB] Installing database..."
    mysql_install_db --user=mysql --datadir=/var/lib/mysql
    
    echo "[MariaDB] Configuring database..."
    mysqld --user=mysql --bootstrap << EOF
USE mysql;
FLUSH PRIVILEGES;
ALTER USER 'root'@'localhost' IDENTIFIED BY '${DB_ROOT_PASSWORD}';
CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${DB_PASSWORD}';
GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';
FLUSH PRIVILEGES;
EOF
    
    echo "[MariaDB] Database initialized successfully"
fi

echo "[MariaDB] Starting MariaDB server..."
exec mysqld --user=mysql --bind-address=0.0.0.0 --port=3306