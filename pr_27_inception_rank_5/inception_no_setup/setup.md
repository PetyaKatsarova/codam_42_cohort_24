# Inception VM Manual Setup

Follow these steps to prepare your VM for the Inception project, without using setup.sh.

## 1. Update and install required packages
```sh
sudo apt update
sudo apt install -y docker.io docker-compose git
```

## 2. (Optional) Add your user to the docker group
```sh
sudo usermod -aG docker $USER
# Log out and log back in for this to take effect
```

## 3. Create required data directories
```sh
mkdir -p ~/data/mariadb
mkdir -p ~/data/wordpress
```

## 4. (Optional) Clone your project repo
```sh
git clone <your-repo-url>
```

## 5. (If needed) Create secrets files
```sh
mkdir -p ./secrets
# Create these files with your chosen passwords (one line per file):
echo 'your_db_password' > ./secrets/db_password.txt
echo 'your_db_root_password' > ./secrets/db_root_password.txt
# (Optional) If your setup uses credentials.txt:
echo -e 'admin_user\nadmin_password' > ./secrets/credentials.txt
```

## 6. (If needed) Set up .env file
Edit `srcs/.env` and fill in your environment variables as required by your docker-compose.yml.

## 7. Start your project
```sh
make all
```

---

You are now ready to use your Inception project without setup.sh!