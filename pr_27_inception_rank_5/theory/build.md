run the Makefile with make up to build and start the containers. make down to stop them, make clean to stop and remove containers, and make fclean to stop, remove containers, and delete volumes (data).

sudo apt update
sudo apt install -y docker.io docker-compose
sudo usermod -aG docker $USER
---------------------------------
docker-compose -v
//if 1.x
sudo apt remove docker-compose
sudo apt install docker-compose

to build:
0. sudo dockerd &
sleep 2

1. sudo systemctl start docker
sudo systemctl enable docker

2. make
3.
============================
sudo chown -R $USER:$USER /home/$USER
==============================

Your VM (Host)
  └─ /home/codam_42_cohort_24/.../inception/
     └─ srcs/requirements/mariadb/
        ├─ Dockerfile  ← "build context" root
        └─ conf/
           └─ mariadb.cnf  ← Gets copied from here
               ↓ COPY ./conf/mariadb.cnf 
          Container Image (being built)
               └─ /etc/mysql/my.cnf  ← Gets placed here

Important: The mariadb.cnf file must exist on your VM at that path, or the build fails.
----------------------------------
newgrp docker — switches your shell to docker group (one-time per session).

