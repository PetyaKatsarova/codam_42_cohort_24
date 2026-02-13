What Are Secrets?
Secrets are just text files containing passwords. Docker reads these files and makes them available inside containers at /run/secrets/.
Step-by-Step: Creating Secrets
Step 1: Understand Your Project Structure
Your docker-compose.yml expects secrets here:
inception/
└── srcs/
    ├── docker-compose.yml
    ├── .env
    ├── requirements/
    └── secrets/           ← This folder
        ├── db_password.txt
        └── db_root_password.txt
Notice in docker-compose.yml:
yamlsecrets:
  db_password:
    file: ../secrets/db_password.txt        # Goes UP one level from srcs/
  db_root_password:
    file: ../secrets/db_root_password.txt
The ../ means "one folder up from srcs/", so secrets should be at inception/secrets/
Step 2: Create the Secrets Folder
From your VM:
bashcd ~/inception_no_setup
mkdir -p secrets
Step 3: Create the Password Files
Create database user password:
bashecho "your_wordpress_db_password_here" > secrets/db_password.txt
Create database root password:
bashecho "your_root_password_here" > secrets/db_root_password.txt
Important: Use strong passwords! For example:
bashecho "Wp_P@ssw0rd_2024!" > secrets/db_password.txt
echo "R00t_Secur3_P@ss!" > secrets/db_root_password.txt
Step 4: Set Correct Permissions (Security)
bashchmod 600 secrets/*.txt
This makes the files readable only by you (owner).
Step 5: Verify Secrets Were Created
bashls -la secrets/
```

Should show:
```
-rw------- 1 pekatsar pekatsar 20 Feb 13 10:00 db_password.txt
-rw------- 1 pekatsar pekatsar 19 Feb 13 10:00 db_root_password.txt
Check the contents (to make sure they're correct):
bashcat secrets/db_password.txt
cat secrets/db_root_password.txt
Step 6: Add to .gitignore
CRITICAL: Don't push passwords to GitHub!
bashecho "secrets/" >> .gitignore
Or create a .gitignore file:
bashcat > .gitignore << EOF
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

bash   DB_PASSWORD=$(cat /run/secrets/db_password)

Uses it to create the database user

Complete Example
bash# Go to your project
cd ~/inception_no_setup

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
inception_no_setup/
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