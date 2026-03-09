# Check vm system
cat /etc/os-release

docker volume inspect srcs_db
docker volume inspect srcs_wp

docker exec wordpress wp redis status --allow-root
docker exec wordpress wp plugin list --allow-root
// after make do:
docker exec wordpress wp config set WP_REDIS_HOST redis --allow-root
docker exec wordpress wp redis enable --allow-root
docker exec wordpress wp redis disable --allow-root



docker exec wordpress wp plugin status --allow-root | grep redis-cache
docker exec wp_redis redis-cli KEYS "*"
--------------------

docker exec wordpress mount | grep /var/www/html
docker exec mariadb mount | grep /var/lib/mysql
docker exec wp_redis mount | grep /data


docker exec wordpress mount | grep /var/www/html
-------------------

docker info | grep "Docker Root Dir"
docker volume inspect srcs_db | grep Mountpoint

sudo mv /var/lib/docker/* /home/pekatsar/data/

docker info | grep "Docker Root Dir"

# TLSv1.2 or TLSv1.3 only
docker exec nginx grep ssl_protocols /etc/nginx/nginx.conf

# Should show nothing
grep -r "latest" srcs/requirements/*/Dockerfile

# Should only show your images (mariadb, wordpress, nginx)
docker images | grep latest

# Show project structure
tree -L 3 inception/

# Verify certificate is self-signed
curl -vk https://pekatsar.42.fr 2>&1 | grep -i "subject\|issuer"

-------------------------------
db
-------------------------------
docker exec -it mariadb mariadb -uroot -p
docker exec -it mariadb mariadb -uwordpress -p -h127.0.0.1

SELECT user, host FROM mysql.user;

USE wordpress;
SHOW TABLES;

select ID, post_author from wp_posts;

-------------------------

# Verify images built from Dockerfile
docker history mariadb | head -5
docker history wordpress | head -5
docker history nginx | head -5

docker inspect mariadb | grep MYSQL_ROOT_PASSWORD
docker exec mariadb ls -la /run/secrets/
docker exec mariadb cat /run/secrets/db_password
# Secrets are in tmpfs (RAM, not disk)
docker exec mariadb mount | grep secrets

docker exec mariadb env | grep MYSQL

docker network rm srcs_inception

docker network ls

# Test inter-container connectivity
docker exec wordpress nc -zv mariadb 3306
docker exec nginx nc -zv wordpress 9000

docker volume ls
# Check volume mount points on host
ls -la ~/data/mariadb
ls -la ~/data/wordpress


# Verify port 3306 listening
docker exec mariadb netstat -tlnp | grep 3306

# Check database exists (wordpress user)
docker exec mariadb mariadb -uwordpress -p$(cat secrets/db_password.txt) -h mariadb -e "SHOW DATABASES;"

# Verify root password is set
docker exec mariadb mariadb -uroot -p$(cat secrets/db_root_password.txt) -e "SELECT 1;"

# Check no test databases
docker exec mariadb mariadb -uroot -p$(cat secrets/db_root_password.txt) -e "SHOW DATABASES;" | grep -i test
# Should show nothing


# Check PHP-FPM is running
docker exec wordpress ps aux | grep php-fpm

# List WordPress users (should show 2)
docker exec wordpress wp user list --allow-root



# Check Nginx is running
docker exec nginx ps aux | grep nginx

# Verify port 443 listening
docker exec nginx netstat -tlnp | grep 443

# Check SSL certificate exists
docker exec nginx ls -la /etc/nginx/ssl/

# Check domain configuration
docker exec wordpress wp option get siteurl --allow-root
# Should show: https://pekatsar.42.fr

---------------------------------------
** images **
# Remove all dangling images (those <none>)
docker image prune -a -f


You can remove unused volumes using docker volume prune.
------------------------------------------
# Simulate a crash (exit code 1 inside container)
docker exec wordpress sh -c "kill 1"

# Wait and check
sleep 15
docker ps | grep wordpress
# Should show wordpress running

docker exec mariadb mariadb -uroot -p$(cat secrets/db_root_password.txt) -e "SHOW DATABASES;" | grep test
docker exec mariadb mariadb -uwordpress -p$(cat secrets/db_password.txt) -h mariadb -e "SHOW DATABASES;"
-------------------------------------------
# Remove ALL unused networks (safe)
docker network prune

# Confirm with 'y'
# This removes inception_inception since no containers use it

# Remove specific network
docker network rm inception_inception
------------------------------------------
docker logs mariadb | tail -20

docker ps -a   
docker stop nginx wordpress mariadb   
docker rm nginx wordpress mariadb     

or:
docker rm -f $(docker ps -aq)

rmv all unused volumes:
docker volume prune

hostname

sudo hostnamectl set-hostname inception

sudo nano /etc/hostname

sudo nano /etc/hosts
```
Change the line with 127.0.1.1 from old hostname to new:
```
127.0.1.1    inception

scp -P 2222 -r inception/ pekatsar@localhost:~/

docker logs wordpress

// secrets:

cd ~/inception && mkdir -p secrets && echo "wordpress_password_123" > secrets/db_password.txt && echo "root_password_456" > secrets/db_root_password.txt && echo "admin_password_123" > secrets/wp_admin_password.txt && echo "user_password_456" > secrets/wp_user_password.txt && ls -la secrets/

https://localhost:8443/
https://localhost:8443/wp-admin/

----------------------------------------
docker volume rm inception_db inception_wp
----------------------------------------
wp:
// no pwd, press only enter
docker exec -it mariadb mariadb -uwordpress -p -h127.0.0.1

SHOW DATABASES;
USE wordpress;
SHOW TABLES;

// login as root:
docker exec -it mariadb mariadb -uroot -p

SELECT user, host FROM mysql.user;
ALTER USER 'wordpress'@'%' IDENTIFIED BY 'Bla42@';
FLUSH PRIVILEGES;
EXIT;

SELECT * FROM wp_users;
SELECT * FROM wp_posts;
SELECT * FROM wp_comments;
----------------------------------------
// -i is interactive, -t tty(allocate a pseudo-TTY)
docker exec -it wordpress ls -l
docker exec -it wordpress ls -l /var/www/html
docker exec -it mariadb ls -l /var/lib/mysql

docker exec -it nginx ls -l /var/www/html
-----------------------------------------

// all containers should be having root processes with PID 1 (the main process of the container)
docker exec -it mariadb ps aux
docker exec -it wordpress ps aux
docker exec -it nginx ps aux

docker exec mariadb mount | grep secrets

docker exec mariadb env | grep MYSQL

docker network ls
