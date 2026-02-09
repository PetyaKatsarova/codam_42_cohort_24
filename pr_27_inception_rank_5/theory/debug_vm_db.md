docker exec -it mariadb mysql -uroot -p


SHOW DATABASES;

SHOW GRANTS FOR 'wordpress'@'%';

--------------------
docker exec -it mariadb sh

ls -l /run/secrets
----------------------
docker exec -it wordpress sh
/var/www/html # ls -l /var/www/html/wp-config.php
ls: /var/www/html/wp-config.php: No such file or directory
/var/www/html # 
