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