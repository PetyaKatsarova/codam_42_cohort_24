To prepare your VM for running Inception (without setup.sh), install these essentials:

Docker Engine
sudo apt update
sudo apt install -y docker.io

Docker Compose
sudo apt install -y docker-compose

(Optional but recommended) Add your user to the docker group:
sudo usermod -aG docker $USER
Then log out and log back in.

(Optional) git, if you want to clone your repo:
sudo apt install -y git