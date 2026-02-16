Port Change Guide - All 3 Containers

// todo: nginx didnt work either way for change of host or container port
NGINX: 9443:7443
docker-compose.yml:
yamlports: ["9443:7443"]
healthcheck:
  test: ["CMD-SHELL", "wget --spider https://localhost:7443 --no-check-certificate || exit 1"]
Dockerfile: EXPOSE 7443
nginx.conf: listen 7443 ssl;
entrypoint.sh:
bashwp config set WP_HOME https://localhost:9443 --allow-root
wp config set WP_SITEURL https://localhost:9443 --allow-root
Access: https://localhost:9443

-----------------------------------------
MariaDB: 5432:5306
docker-compose.yml:
yamlports: ["5432:5306"]
healthcheck:
  test: ["CMD", "mysqladmin", "ping", "-P", "5306"]
Dockerfile: EXPOSE 5306
my.cnf:
ini[mysqld]
port = 5306
.env: DB_HOST=mariadb:5306
entrypoint.sh: while ! nc -z mariadb 5306; do sleep 1; done
Access: mysql -h localhost -P 5432

-------------------------------------------
WordPress: 10000:10900
docker-compose.yml:
yamlports: ["10000:10900"]
healthcheck:
  test: ["CMD", "nc", "-z", "localhost", "10900"]
Dockerfile: EXPOSE 10900
php-fpm.conf: listen = 0.0.0.0:10900
nginx.conf: fastcgi_pass wordpress:10900;
-------------------------------------
WordPress Port Change Guide -> works
Current Setup

Container port: 9000 (PHP-FPM default)
No host port exposed (internal only)


Change to: 10000:10900
1. docker-compose.yml
yamlwordpress:
  ports:
    - "10000:10900"  # Add this line
  healthcheck:
    test: ["CMD", "nc", "-z", "localhost", "10900"]  # Change 9000 → 10900
2. Dockerfile (wordpress)
dockerfileEXPOSE 10900  # Change from 9000
3. php-fpm.conf
Location: requirements/wordpress/conf/php-fpm.conf
inilisten = 0.0.0.0:10900  # Change from 9000 or /run/php/php-fpm.sock
4. nginx.conf
Location: requirements/nginx/conf/nginx.conf
nginxlocation ~ \.php$ {
    fastcgi_pass wordpress:10900;  # Change from wordpress:9000
}

Why Each Change
docker-compose ports: Expose to host (optional, usually not needed for PHP-FPM)
healthcheck: Must check container's internal port (10900)
php-fpm.conf: Makes PHP-FPM listen on 10900 instead of 9000
nginx.conf: Tells nginx where to forward PHP requests
