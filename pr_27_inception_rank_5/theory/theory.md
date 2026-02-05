**.bashrc** is the “bash run commands” file. It's a shell script that runs every time you start an interactive non-login Bash shell. It typically contains:

Aliases (e.g., alias ll='ls -la')
Environment variables (e.g., export PATH=...)
Prompt configuration (PS1)
Shell options (shopt, set)
Functions and custom commands
Tool initializations (e.g., nvm, conda)

--------------------------------------------

A **locale** tells programs your language, character encoding, number/date formats, and sorting rules.
It's used by tools like apt, perl, bash, and editors to format text and handle UTF-8 correctly.
a warning means some locales you set (e.g., nl_NL.UTF-8) aren't installed, so Perl falls back.
Fix steps (VM):

Check installed locales:
locale -a
Generate needed locales:
sudo locale-gen en_US.UTF-8
Set defaults:
sudo update-locale LANG=en_US.UTF-8 LC_ALL=en_US.UTF-8
Log out/in (or reboot).

debug:
grep -R "LC_" ~/.bashrc ~/.profile ~/.bash_profile /etc/default/locale /etc/environment

unset LC_ALL LC_CTYPE LC_NUMERIC LC_TIME LC_MESSAGES LC_MONETARY LC_ADDRESS LC_IDENTIFICATION LC_MEASUREMENT LC_PAPER LC_TELEPHONE LC_NAME

sudo update-locale LANG=en_US.UTF-8 LC_ALL=en_US.UTF-8

logout ssh and login again, check:
locale

---------------------------------------------------
drwxrwxr-x 3 wil wil 4096 avril 42 20:42 
4096 = size in bytes (directory entries; directories often show 4096).
avril 42 20:42 = last modified date/time (April 42 is just the locale's date format; “42” is the day).
3 right after permissions = number of hard links to that directory.


--------------------------------------------------------
project skeleton (Makefile + srcs folder with docker-compose.yml, .env, and requirements/{nginx,wordpress,mariadb,tools}).

todo:
Sensitive files like .env/secrets can be created on the VM and kept out of Git.

---------------------------------------
1. 
mkdir -p srcs/requirements/{nginx,wordpress,mariadb,tools}

-p tells mkdir to create parent directories as needed and not error if they already exist.

2. 
touch Makefile srcs/docker-compose.yml srcs/.env
---------------------------------------------
**ports** map host ports to container ports using "HOST:CONTAINER".

"443:443" means:
Host port 443 → Container port 443 (NGINX TLS). transport layer 
security (TLS) is the successor to SSL and provides encryption for secure communication over the internet. TLS 1.2 and 1.3 are the latest versions, offering improved security and performance.
Encryption: Protects data from being intercepted or read in transit
Authentication: Verifies the server is legitimate (using certificates like the self-signed one in your theory notes)
HTTPS: The "S" in HTTPS stands for "Secure"—it's HTTP over TLS
Ports: TLS typically uses port 443 (vs. unencrypted HTTP on port 80)
Successor to SSL: TLS replaced the older SSL (Secure Sockets Layer) protocol

Users connect to host 443; Docker forwards to NGINX inside container.
To change the public port (outside):

Use "8443:443" → access via https://yourdomain:8443.
To change the container port (inside):

You must also change NGINX to listen on that port. Example "8443:8443" with NGINX listening on 8443.
Rule of thumb:

Left side = public port on VM.
Right side = port your service listens on inside the container.
-----
VM (Host machine): Debian Trixie

Your actual computer/virtual machine
Runs Docker daemon
You develop, build, and run containers from here
Containers (Inside Docker): Alpine 3.16

Nginx container → Alpine
MariaDB container → Alpine
WordPress container → Alpine
Why This Works Perfectly:
Host OS (Debian) doesn't matter for container images
Container images (Alpine) are isolated, self-contained environments
Docker abstracts the host OS completely
Your Alpine containers will run identically on Debian, Ubuntu, macOS,
------------------------------------------------------------
Alpine  3.16 for the docker images is chosen because:

 Very lightweight (5MB base image)  perfect for containers
Smaller image = faster pull/build/startup
Less bloat = fewer vulnerabilities
Industry standard for Docker (used in production)

-----------------------------------------

For nginx, permissions for created dir aren't usually an issue since:

Nginx runs as the nginx user (created automatically by the package)
/etc/nginx/ssl is readable by nginx
If you need explicit permissions, you could add: RUN chmod 755 /etc/nginx/ssl
-----------------------------------------
**Dockerfile** is a text file with instructions to build a Docker image.
It defines the base image, copies files, installs packages, sets environment variables, and specifies commands to run when the container starts.
Docker reads the Dockerfile line by line to create an image layer by layer.
Common instructions include:
FROM: base image
COPY/ADD: copy files into the image
RUN: run commands during build
ENV: set environment variables
CMD/ENTRYPOINT: specify the command to run when the container starts
EXPOSE: declare ports the container listens on
WORKDIR: set working directory


RUN apk update && apk add --no-cache nginx openssl

Install nginx (web server) and openssl (for SSL/TLS certificates). --no-cache reduces image size by not storing package cache.
------------------------------------------
What is package cache?
When you run apk add, Alpine downloads packages and stores metadata in /var/cache/apk/. This cache helps future installs run faster (packages don't need re-downloading).

In a Docker image, the cache is stored as a layer and increases image size unnecessarily.

WITH cache (apk add nginx openssl)
Pros:

Faster if you install more packages later in same Dockerfile
Can troubleshoot if install fails
Cons:

Image size bloated (+10-50 MB depending on packages)
Cache never used after image is built (one-time use)
Violates Docker best practices
----------------------------------
Create directory to store SSL certificates.
mkdir -p /etc/nginx/ssl
-------------------------------------------------
Generate a self-signed SSL certificate valid for 365 days:

-x509: Self-signed certificate
-nodes: No password encryption on private key
-newkey rsa:2048: Create 2048-bit RSA key
-keyout: Save private key
-out: Save certificate
-subj: Certificate metadata (country, city, organization, domain)

openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/private.key \
    -out /etc/nginx/ssl/certificate.crt \
    -subj "/C=NL/ST=Amsterdam/L=Amsterdam/O=42/CN=inception"
-------------------------------------------------

Copy custom nginx configuration from your host into the container.

COPY ./conf/nginx.conf /etc/nginx/nginx.conf
------------------------------------------------

Document that the container listens on port 443 (HTTPS). This doesn't actually open the port—docker-compose.yml does that with ports: "443:443".

EXPOSE 443
-------------------------------------------------
Run nginx in foreground mode (required for Docker containers to keep running).
CMD ["nginx", "-g", "daemon off;"]
-------------------------------------------------
In summary, this Dockerfile:
Uses Alpine Linux as base
Installs nginx and openssl
Creates SSL directory
Generates self-signed SSL certificate
Copies custom nginx config
Exposes port 443
Runs nginx in foreground mode
----------------------------------------
DETAILS:

What is x509?
x509 is an international standard format for digital certificates. It's like a "digital ID card" that proves your website is who it claims to be.
Structure:
Certificate (x509)
├── Public Key (shared with browsers)
├── Signature (proves authenticity)
├── Validity dates (expiration)
├── Subject info (your domain details)
└── Issuer info (who signed it)

You create a self-signed certificate (you are your own issuer), which browsers will warn about, but it works for testing.
------------------------------------------------

the secrets folder stores sensitive credentials that should NOT be submitted in the repo.

What goes in secrets/:

db_password.txt — MariaDB user password
db_root_password.txt — MariaDB root password
credentials.txt — WordPress admin credentials

Docker Secrets mechanism passes these files to containers without hardcoding passwords. In your docker-compose.yml, you reference them like:

services:
  mariadb:
    secrets:
      - db_password
      - db_root_password
secrets:
  db_password:
    file: ./secrets/db_password.txt
  db_root_password:
    file: ./secrets/db_root_password.txt
  credentials:
    file: ./secrets/credentials.txt

Create the secrets folder: mkdir -p secrets
Add secret files with passwords (one password per file)
Add secrets/ to .gitignore
The secrets/ folder never goes to git—only the structure and logic in your Dockerfiles/docker-compose that references them.
-----------------------------------------

NGINX (pronounced "engine-x") is a web server and reverse proxy.

Its roles in Inception:

Web Server — Serves HTTPS traffic on port 443
Reverse Proxy — Forwards requests to WordPress (php-fpm) backend
TLS/SSL Handler — Encrypts communication with clients
Entry Point — Only service exposed to the internet; others are hidden
Architecture:
Client (browser) 
    ↓ HTTPS (port 443)
NGINX (reverse proxy)
    ↓ HTTP (internal network)
WordPress + PHP-FPM
    ↓
MariaDB

Security: Only NGINX is exposed; databases are hidden behind it
Performance: NGINX is lightweight, fast at handling connections
Flexibility: Easy to add load balancing, caching, or multiple backends
-----------------------------------------
inception/
├── Makefile
├── .env
├── .gitignore
├── secrets/
│   ├── db_password.txt
│   ├── db_root_password.txt
│   └── credentials.txt
└── srcs/
    ├── docker-compose.yml
    └── requirements/
        ├── nginx/
        │   ├── Dockerfile
        │   ├── conf/
        │   │   └── nginx.conf
        │   └── tools/
        ├── mariadb/
        │   ├── Dockerfile
        │   ├── conf/
        │   └── tools/
        └── wordpress/
            ├── Dockerfile
            └── tools/
------------------------------------------
The version field specifies the Docker Compose file format version — not Docker itself, but the YAML syntax/schema.

Different versions support different features:

version: 2.x — Older, wider compatibility with old Docker installations
version: 3.x — Newer, designed for Docker Swarm, more features
3.3 — Good balance; supports most modern features
3.8 — Newest, but requires newer docker-compose
Each version defines what keys you can use in the file (like depends_on, networks, volumes, etc.).
-------------------------------------------

networks:
  inception:
    driver: bridge

    Bridge driver = virtual network switch.

Containers connected to same bridge can ping/reach each other by container name. Isolated from other networks/host.
WordPress connects to mariadb:3306 (DNS resolution)
NGINX connects to wordpress:9000
Without bridge: Containers isolated, can't reach each other by name.

driver = network type in Docker.

bridge (default):

Virtual network switch
Containers isolated, communicate by name
Used for local dev/Inception
Other options:

host — Container shares host network (no isolation)
overlay — Multi-host networks (Docker Swarm)
none — No network
macvlan — Containers get real MAC addresses

driver = mechanism (how it works internally)
network type = category (bridge, host, etc.)

What it does = allows containers to communicate.

Tell containers to connect:
services:
  mariadb:
    networks:
      - inception  # This container joins "inception" network
  
  wordpress:
    networks:
      - inception  # This container joins same network

networks:
  inception:      # Define network at bottom
    driver: bridge

  Containers on same network can reach each other by name (mariadb:3306, wordpress:9000).
  ------------------------------------------
MYSQL_PASSWORD_FILE tells MariaDB: "Read password from file /run/secrets/db_password instead of env var."

Secret file ../secrets/db_password.txt exists on your VM
Docker mounts it inside container at /run/secrets/db_password
MariaDB reads that file and uses content as password
Why: More secure than storing password in environment variable (which could leak in logs).

Mount = makes file accessible at that path, but doesn't copy it.

Copy = makes a duplicate of the file into image.

Difference:

Mount: Original file stays on VM, container sees it at /run/secrets/db_password
Copy: File duplicated into image (insecure for secrets)
Docker secrets use mount to keep credentials off the image layer. Only container has access at runtime.

Mount is a concept (linking files). Docker automatically handles it when you declare secrets: in docker-compose.yml. Not a command you run.

Docker does this automatically:

Reads your VM file ../secrets/db_password.txt
Makes it visible inside container at /run/secrets/db_password
MariaDB reads it at runtime. You never see the password in the image or environment variables.
----------------------------------
user1 is a regular WordPress user (non-admin).

Used for:

WordPress login — after setup, log in as user1:user1_password_123
Created during WordPress setup — via entry entrypoint script using wp-cli commands. there is srcs/requirements/mariadb/tools/entrypoint.sh
----------------------------------------------------------
0.0.0.0 = listen on all network interfaces. Allows other containers to connect (wordpress, nginx).

Daemon = background process that runs indefinitely.

mysqld_safe = wrapper that starts MySQL and auto-restarts if it crashes.

exec = replaces shell with mysqld_safe process. Docker monitors it; if it stops, container stops.
--------------------------------

mariadb/conf/mariadb.cnf is the custom configuration file for MariaDB. It must exist on your VM at that path before building the image, or the build will fail.

[mysqld] — Config section for MySQL daemon

skip-networking=OFF — Enable networking. OFF means networking IS enabled (counter-intuitive).

bind-address=0.0.0.0 — Listen on all interfaces. Without this, might be localhost-only (containers can't reach).

port=3306 — Standard MySQL/MariaDB port.

sql_mode="" — No strict SQL rules. Allows flexibility.

Can you skip this file?

MariaDB has built-in defaults. best practise is to have it, because:

Default bind might be localhost (breaks container networking)
Explicit config ensures consistency across systems
-------------------------------------------------

mariadb.cnf port=3306 = what port MariaDB listens on INSIDE container.

docker-compose.yml ports: (for MariaDB) = (you don't have this, which is correct) would expose to HOST machine.

For Inception:

MariaDB only accessed by WordPress container internally via mariadb:3306
Don't need ports: mapping for MariaDB (it's not exposed to host)
Keep port=3306 in .cnf for internal listening
NGINX has ports: 443:443 because it's exposed to users outside containers.
--------------------------------
.dockerignore in mariadb foder:
 excludes files from Docker build context (keeps image smaller).
 ----------------------

 Container = isolated lightweight environment with its own filesystem.

When you start a container:

It has only files from the image (Alpine base + what you COPY/RUN)
It does NOT have access to your VM filesystem
It needs its own copy of everything it needs
Why copy entrypoint.sh:

VM has: /home/.../mariadb/tools/entrypoint.sh (your file)
Container starts with empty filesystem
COPY brings it into container filesystem at /entrypoint.sh
Now container can execute it
Without COPY: Container has no entrypoint.sh → can't run it → container fails.
---------------------------------------------
Wordpress waits for MariaDB to actually be readyNginx waits for WordPress to actually be readyNo "connection refused" errors due to timing issues
--------------------
debug wordpress:
docker-compose -f srcs/docker-compose.yml logs wordpress 2>&1 | tail -50
----------------------
the volumes are in ls -la ~/data/ in the VM. This is where MariaDB stores its data files persistently.
----------------
docker volume ls
docker volume inspect srcs_wp


