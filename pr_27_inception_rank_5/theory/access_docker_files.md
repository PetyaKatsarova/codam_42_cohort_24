Files in Your Volumes (Easiest)
These are real folders on your machine:
ls -la ~/data/wordpress/      # WordPress files
ls -la ~/data/mariadb/        # Database files
You can edit these directly - containers see the changes!

-------------------------
Inside Running Container
Access files while container is running:
docker exec srcs-wordpress-1 ls -la /var/www/html/
docker exec srcs-wordpress-1 cat /etc/php8/php-fpm.d/www.conf
docker exec srcs-mariadb-1 ls -la /var/lib/mysql/
--------------------------
Docker stores managed volumes and images at:
sudo ls -la /var/lib/docker/
sudo ls -la /var/lib/docker/volumes/
Warning: Requires sudo, and these are Docker internals - don't modify directly.
--------------------------
!NB!!

scp -P 2222 -r inception pekatsar@localhost:/home/pekatsar/
