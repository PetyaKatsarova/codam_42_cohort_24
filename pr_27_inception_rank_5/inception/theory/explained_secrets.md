Docker Secrets Tutorial - Inception 42 Project
 Docker Swarm is not used here
Reasons:

Inception requires docker-compose, not Swarm
Swarm secrets (docker secret create) only work in Swarm mode
Subject explicitly requires docker-compose
File-based secrets are simpler and sufficient


Docker secrets — storing confidential info

Purpose: Store sensitive info like passwords, API keys, root credentials securely.

Secrets are mounted inside the container, never baked into Docker images.

Create secrets
echo "rootpassword123" | docker secret create db_root_password -
echo "userpassword123" | docker secret create db_password -
This stores the passwords securely in Docker swarm.

Step 2: Reference secrets in docker-compose.yml
services:
  mariadb:
    image: mariadb:11
    container_name: mariadb
    env_file:
      - .env
    environment:
      MYSQL_DATABASE: ${MYSQL_DATABASE}        # from .env
      MYSQL_USER: ${MYSQL_USER}                # from .env
      MYSQL_PASSWORD_FILE: /run/secrets/db_password
      MYSQL_ROOT_PASSWORD_FILE: /run/secrets/db_root_password
    secrets:
      - db_password
      - db_root_password

    wordpress:
    image: wordpress:6.4-php8.3-fpm
    env_file:
      - .env
    environment:
      WORDPRESS_DB_NAME: ${MYSQL_DATABASE}       # from .env
      WORDPRESS_DB_USER: ${MYSQL_USER}          # from .env
      WORDPRESS_DB_PASSWORD_FILE: /run/secrets/db_password

secrets:
  db_password:
    external: true
  db_root_password:
    external: true


MYSQL_PASSWORD_FILE points to the secret inside the container (/run/secrets/...).

The container reads it at runtime, never stored in image.

Do not write secrets in .env or Dockerfile.

Using secrets inside entrypoint scripts

------------------------
What Are Secrets?
Secrets are just text files containing passwords. Docker reads these files and makes them available inside containers at /run/secrets/.

Your docker-compose.yml expects secrets here:
inception/
└── srcs/
    ├── docker-compose.yml
    ├── .env
    ├── requirements/
    └── secrets/           ← This folder
        ├── db_password.txt
        └── db_root_password.txt

Step 2: Create the Secrets Folder
From your VM:
cd ~/inception
mkdir -p secrets
Step 3: Create the Password Files
Create database user password:
echo "your_wordpress_db_password_here" > secrets/db_password.txt
Create database root password:
echo "your_root_password_here" > secrets/db_root_password.txt
Important: Use strong passwords! For example:
echo "Wp_P@ssw0rd_2024!" > secrets/db_password.txt
echo "R00t_Secur3_P@ss!" > secrets/db_root_password.txt
Step 4: Set Correct Permissions (Security)
chmod 600 secrets/*.txt
This makes the files readable only by you (owner).
Step 5: Verify Secrets Were Created
ls -la secrets/
```

Should show:
```
-rw------- 1 pekatsar pekatsar 20 Feb 13 10:00 db_password.txt
-rw------- 1 pekatsar pekatsar 19 Feb 13 10:00 db_root_password.txt
Check the contents (to make sure they're correct):
cat secrets/db_password.txt
cat secrets/db_root_password.txt
Step 6: Add to .gitignore
CRITICAL: Don't push passwords to GitHub!
echo "secrets/" >> .gitignore
Or create a .gitignore file:
cat > .gitignore << EOF
secrets/
.env
*.swp
*~
EOF
Step 7: How Secrets Work in Docker
When you run docker-compose up, Docker:

Reads secrets/db_password.txt from your host
Mounts it inside the MariaDB container at /run/secrets/db_password
Your entrypoint.sh reads it:

   DB_PASSWORD=$(cat /run/secrets/db_password)

Uses it to create the database user

Complete Example
# Go to your project
cd ~/inception

# Create secrets folder
mkdir -p secrets

# Create passwords (change these to your own!)
echo "MyWordPressPass123!" > secrets/db_password.txt
echo "MyRootPass456!" > secrets/db_root_password.txt

# Secure the files
chmod 600 secrets/*.txt

# Verify
ls -la secrets/
cat secrets/db_password.txt

# Make sure git ignores them
echo "secrets/" >> .gitignore
```

## What Should Your Final Structure Look Like?
```
inception/
├── .gitignore
├── Makefile
├── secrets/                           ← YOU CREATE THIS
│   ├── db_password.txt               ← YOU CREATE THIS
│   └── db_root_password.txt          ← YOU CREATE THIS
└── srcs/
    ├── .env
    ├── docker-compose.yml
    └── requirements/
        ├── mariadb/
        ├── nginx/
        └── wordpress/

----------------------------------------
for testing can create credentials.txt
cat > credentials.txt << EOF
Database Root Password: (content of secrets/db_root_password.txt)
Database User Password: (content of secrets/db_password.txt)
WordPress Admin: pekatsar / (your admin password from .env)
WordPress User: editor / (your user password from .env)
EOF