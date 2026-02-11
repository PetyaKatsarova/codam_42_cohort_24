502 Bad Gateway
502 = Nginx can't reach PHP-FPM

Nginx and PHP-FPM are separate containers
Nginx listens on port 443
PHP-FPM listens on port 9000
Nginx needs to connect to PHP-FPM to execute PHP code
If connection fails → 502 Bad Gateway error
Possible causes:
- PHP-FPM container not running
- Nginx misconfigured to connect to wrong port or hostname
- Network issues between containers
To fix:
1. Check if PHP-FPM container is running:
docker ps
2. Check Nginx configuration for correct PHP-FPM connection settings
3. Check Docker network settings to ensure containers can communicate
4. Restart containers if needed:
docker-compose restart 

debug:
1. docker ps // check if all containers are running
2. docker exec srcs-wordpress-1 netstat -tlnp | grep 9000 // check if PHP-FPM is listening on port 9000
=======================================
docker exec srcs-wordpress-1 cat /etc/php8/php-fpm.d/www.conf | grep "listen ="
listen = 127.0.0.1:9000
;pm.status_listen = 127.0.0.1:9001

docker exec	Execute command inside container
srcs-wordpress-1	In the WordPress container
cat /etc/php8/php-fpm.d/www.conf	Read the php-fpm config file inside container
|	Pipe (send output to next command)
grep "listen ="	Search for lines with "listen ="

The Dockerfile likely isn't copying our custom config file at all. It's using the default Alpine PHP-FPM config which has listen = 127.0.0.1:9000.
-----------------
docker exec srcs-mariadb-1 mysql -u root -p$(cat ./secrets/db_root_password.txt) -e "SHOW DATABASES; SELECT user FROM mysql.user WHERE user='wordpress';"


