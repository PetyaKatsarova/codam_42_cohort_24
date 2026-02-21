
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
