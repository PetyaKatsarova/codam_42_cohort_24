
sudo mkdir -p /home/pekatsar/data

sudo nano /etc/docker/daemon.json
# Add the JSON above

{
  "data-root": "/home/pekatsar/data"
}
