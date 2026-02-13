docker ps -a   
docker stop nginx wordpress mariadb   
docker rm nginx wordpress mariadb     

or:
docker rm -f $(docker ps -aq)

rmv all unused volumes:
docker volume prune

docker volume rm srcs_db srcs_wp

ssh -p 2222 pekatsar@localhost

hostname

sudo hostnamectl set-hostname inception

sudo nano /etc/hostname

sudo nano /etc/hosts
```
Change the line with 127.0.1.1 from old hostname to new:
```
127.0.1.1    inception

scp -P 2222 -r inception_no_setup/ pekatsar@localhost:~/