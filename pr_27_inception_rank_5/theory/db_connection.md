# Database Connection Setup

## How Databases Are Created

### Step 1: MariaDB Container Starts
docker-compose up
MariaDB initialization begins. The entrypoint script runs before the database service becomes available.

**Theory:** MariaDB runs the entrypoint script first, which can create databases and users before the main mysqld process starts.

### Step 2: Entrypoint Script Must Create Database & User
The script should contain:

```bash
#!/bin/bash
set -e

# Create wordpress database
mysql -u root -p${MYSQL_ROOT_PASSWORD} -e "CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};"

# Create wordpress user with password
mysql -u root -p${MYSQL_ROOT_PASSWORD} -e "CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';"

# Grant privileges to wordpress user
mysql -u root -p${MYSQL_ROOT_PASSWORD} -e "GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';"

# Flush privileges to apply changes
mysql -u root -p${MYSQL_ROOT_PASSWORD} -e "FLUSH PRIVILEGES;"

# Start MariaDB
exec mysqld
```

### Step 3: WordPress Connects
WordPress attempts to connect:
- Host: `mariadb` (Docker internal network)
- Database: `wordpress`
- User: `wordpress`
- Password: (from secrets file)

**Currently fails:** Database and user don't exist.

============================
docker exec srcs-mariadb-1 mysql -u root -p$(cat ./secrets/db_root_password.txt) -e "SHOW DATABASES;"

docker exec srcs-mariadb-1 mysql -u root -p$(cat ./secrets/db_root_password.txt) -e "SELECT user FROM mysql.user WHERE user='wordpress';"

docker logs srcs-wordpress-1 | tail -30

docker logs srcs-wordpress-1
[WordPress] Waiting for MariaDB to be ready...
[WordPress] MariaDB is ready!
[WordPress] Checking for WordPress files...
[WordPress] Downloading and extracting WordPress...
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed
100 25.8M  100 25.8M    0     0  7921k      0  0:00:03  0:00:03 --:--:-- 7919k
[WordPress] Setting permissions...
[WordPress] Starting PHP-FPM...

docker exec srcs-wordpress-1 cat /var/www/html/wp-config.php
============================
cat /etc/hosts | grep inception

docker logs srcs-nginx-1

docker inspect srcs-nginx-1 | grep -A 20 "Health"