Imagine you're building a house (WordPress website). You need:

A foundation (MariaDB database)
The house itself (WordPress)
A front door (Nginx)

Step 1: Building the Foundation (MariaDB Container)
Your Dockerfile for MariaDB is like a recipe:

Step 1: Building the Foundation (MariaDB Container)
Your Dockerfile for MariaDB is like a recipe:
FROM alpine:3.21                    # Start with a tiny Linux system
RUN apk add mariadb                 # Install database software
COPY ./tools/entrypoint.sh          # Copy setup instructions
ENTRYPOINT ["/entrypoint.sh"]       # Run setup when container starts
```

When the container starts, it runs **entrypoint.sh** which:
1. Initializes the database (creates the database files)
2. Reads secrets from `/run/secrets/db_password` and `/run/secrets/db_root_password`
3. Creates a database named "wordpress" (from `.env` file)
4. Creates a user "wordpress" with the password from secrets
5. Starts the MariaDB server

### Step 2: The Secrets Folder

The **secrets folder** contains two files with passwords:
- `db_password.txt` - password for WordPress to access database
- `db_root_password.txt` - master password for database admin

**Why secrets?** It's like keeping your house key in a locked box instead of writing it on the door!

Docker mounts these files into the container at `/run/secrets/` so the entrypoint script can read them but they never show up in logs or configs.

### Step 3: How WordPress Connects

When you visit `https://localhost:8443/wp-admin/setup-config.php?step=1`, WordPress asks you:
- Database name: `wordpress` (from `.env`)
- Username: `wordpress` (from `.env`)
- Password: (the content of `db_password.txt`)
- Database host: `mariadb` (from `.env`)

**BUT** - if your entrypoint scripts are done right, you shouldn't see this setup page at all! The WordPress entrypoint should automatically create `wp-config.php` with all this info.

### Step 4: The Magic Connection

Here's how they talk to each other:
```
[WordPress Container]
    ↓ "Hey mariadb, I need to store some data!"
[Docker Network: 'inception']
    ↓ DNS resolves 'mariadb' to MariaDB container's IP
[MariaDB Container]
    ↓ "Sure! What's the password?"
[WordPress Container]
    ↓ Reads /run/secrets/db_password
    ↓ Sends password
[MariaDB Container]
    ↓ "Password correct! Here's your database."
	------------------------------------------------------------

	The Complete Flow:

make all runs
MariaDB container starts first

Runs entrypoint.sh
Creates database "wordpress"
Creates user "wordpress" with secret password
Waits for connections


WordPress container starts (waits for MariaDB to be healthy)

Runs its entrypoint.sh
Downloads WordPress files
Creates wp-config.php with database info
Connects to mariadb:3306 using credentials


Nginx starts last

Forwards web requests to WordPress
Shows you the website
======================================================
You need to add WP-CLI (WordPress Command Line Interface) to automate the setup.