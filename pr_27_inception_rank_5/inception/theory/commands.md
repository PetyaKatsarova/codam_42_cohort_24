# Check system
cat /etc/os-release

// TLSv1.2 or TLSv1.3 only
grep ssl_protocols srcs/requirements/nginx/conf/nginx.conf

grep -r "latest" srcs/requirements/*/Dockerfile
# Should show nothing

docker images | grep latest
# Should only show your images (mariadb, wordpress, nginx)

# Show project structure
tree -L 3 inception/

# Show no passwords in .env
cat srcs/.env | grep -i pass
# Should show nothing

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

docker network ls

# Test inter-container connectivity
docker exec wordpress nc -zv mariadb 3306
docker exec nginx nc -zv wordpress 9000

# port
netstat -tlnp

docker volume ls
# Check volume mount points on host
ls -la ~/data/mariadb
ls -la ~/data/wordpress

# Check TLS version (should be TLSv1.2 or TLSv1.3)
docker exec nginx cat /etc/nginx/nginx.conf | grep ssl_protocols


# Verify certificate is self-signed
curl -vk https://pekatsar.42.fr 2>&1 | grep -i "subject\|issuer"


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