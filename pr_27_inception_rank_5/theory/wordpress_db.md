Enter your MariaDB/MySQL container:

docker exec -it mariadb bash


Login to MySQL:

mysql -u root -p


Select your WordPress database:

USE wordpress;-----------------------------------
----------------------

docker exec -it mariadb sh
chmod 644 /etc/mysql/my.cnf

mysql -u root -p

SHOW DATABASES;
USE wordpress;
SELECT ID, user_login FROM wp_users;

USE wordpress;
SELECT ID, user_login FROM wp_users;
SELECT user_login FROM wp_users 
WHERE user_login LIKE '%admin%';


WordPress automatically creates tables in the database when the WordPress container starts and connects to the DB.

Any SQL you run before WordPress starts will fail if it targets WordPress tables.


docker exec -it mariadb sh
mysql -u root -p
USE wordpress;
SELECT ID, user_login FROM wp_users;




