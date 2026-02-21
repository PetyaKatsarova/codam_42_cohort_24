Subjects requires to use named and specifically no bind mounts for volumes.
Decision was made to move all docker files to /home/pekatsar/data and change the docker data-root to that path. This way we can use named volumes and still have the data on the host machine, which is required for the project.

sudo mkdir -p /home/pekatsar/data

sudo nano /etc/docker/daemon.json
# Add the JSON above

{
  "data-root": "/home/pekatsar/data"
}
sudo mkdir -p /home/pekatsar/data/mariadb /home/pekatsar/data/wordpress
sudo chown -R $USER:$USER /home/pekatsar/data

sudo systemctl restart docker
// in wsl2 use:
sudo service docker restart

ps aux | grep docker
sudo kill 1863
sudo rm /var/run/docker.pid
sudo dockerd &
docker info | grep "Docker Root Dir"
