
// ssl protocol: 
docker exec nginx nginx -T | grep ssl_protocols

//Verify NO other services in nginx container:
docker exec nginx ps aux

//WordPress Container with php-fpm Only (NO nginx)

docker exec wordpress ps aux | grep php-fpm

// verify no nginx in wordpress container:
docker exec wordpress which nginx

// verify php-fpm listending on port 9000 in wordpress container:
docker exec wordpress netstat -tuln | grep 9000

// verify wordpress files exist
docker exec wordpress ls -la /var/www/html | head -10

docker volume ls | grep db
docker volume inspect srcs_db

ls -la ~/data/wordpress/

Check volume type:
bashdocker inspect mariadb | grep '"Type"'
Expected: "Type": "volume" (NOT "Type": "bind")

# nginx -> wordpress
docker exec nginx ping -c 2 wordpress

# wordpress -> mariadb
docker exec wordpress ping -c 2 mariadb

# nginx -> mariadb
docker exec nginx ping -c 2 mariadb

cat srcs/docker-compose.yml | grep restart
    restart: unless-stopped
    restart: unless-stopped
    restart: unless-stopped

    # Kill nginx process
docker exec nginx kill 1

# Wait 2 seconds
sleep 2

# Check if container restarted
docker ps | grep nginx

# In one terminal, watch events:
docker events --filter 'type=container' --filter 'event=restart'

# In another terminal, kill a container:
docker exec nginx kill 1

docker exec nginx ps aux
----------------------------------
// verify 2 users in wordpress database:
docker exec -it mariadb sh
mysql -u root -p
USE WORDPRESS;
SELECT ID, user_login FROM wp_users;














1. A Docker container that contains NGINX with TLSv1.2 or TLSv1.3 only:
in nginx.conf have:  ssl_protocols TLSv1.2 TLSv1.3;
openssl s_client -connect localhost:443 -tls1_2 < /dev/null 2>&1 | grep "Protocol"
    #!/bin/bash

echo "Testing TLSv1.2 (should work):"
openssl s_client -connect localhost:443 -tls1_2 < /dev/null 2>&1 | grep "Protocol"

echo -e "\nTesting TLSv1.3 (should work):"
openssl s_client -connect localhost:443 -tls1_3 < /dev/null 2>&1 | grep "Protocol"

echo -e "\nTesting TLSv1.1 (should FAIL):"
openssl s_client -connect localhost:443 -tls1_1 < /dev/null 2>&1 | grep -E "Protocol|error"

echo -e "\nTesting TLSv1.0 (should FAIL):"
openssl s_client -connect localhost:443 -tls1 < /dev/null 2>&1 | grep -E "Protocol|error"
---------------------------------
2. A Docker container that contains WordPress + php-fpm (it must be installed and
configured) only, without nginx.

docker exec wordpress ps aux
docker exec mariadb which nginx // checks no nginx installed
----------------------------------
4. & 5. docker volume ls
docker volume inspect srcs_db



**Theory**
TLS (Transport Layer Security) is the encryption protocol that makes HTTPS secure.

TLSv1.2 and TLSv1.3 are the modern, secure versions
TLSv1.0 and TLSv1.1 are old and insecure (deprecated)
------------------------
** bind mount volume:
Maps a specific directory on YOUR computer (/home/pettop/data/mariadb) directly into the container
You control exactly where the data lives
Data is stored in a user-defined location
volumes:
  db:
    driver: local
    driver_opts:
      type: none
      o: bind
      device: /home/pettop/data/mariadb  # Points to YOUR specific path
Works like a "shared folder" between host and container

** named volume:
volumes:
  db:
    driver: local  # Docker manages everything automatically

Docker automatically creates and manages the storage location
Data is stored in Docker's own directory (/var/lib/docker/volumes/)
You don't control the exact path
Docker handles permissions, ownership, and management

compare:
# Bind mount - breaks on different computers:
device: /home/pettop/data/mariadb  # What if evaluator's username isn't "pettop"?

# Named volume - works everywhere:
db:
  driver: local  # Docker handles it automatically