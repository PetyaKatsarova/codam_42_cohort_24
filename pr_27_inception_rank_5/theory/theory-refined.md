# File owned by root, but nobody can do anything
-rw------- root root  myfile.txt

# Change owner to mysql (now mysql "owns" it)
chown mysql:mysql myfile.txt
-rw------- mysql mysql myfile.txt

# Change permissions so mysql can execute it
chmod u+x myfile.txt
-rwx------ mysql mysql myfile.txt
======================================================================
Volume = Persistent Storage Bridge
A volume connects your host machine (your computer) to a container (Docker app), so data survives when the container stops.

**with volumes**
Container stops → Data PRESERVED on your machine

docker run -v /home/pettop/data/mariadb:/var/lib/mysql mariadb
# Container starts, creates database in /var/lib/mysql (inside container)
# BUT it's actually writing to /home/pettop/data/mariadb (on your machine)
# You stop container
# DATA STILL EXISTS on your machine
# Restart container, data is still there!

Volume = USB drive connected to a computer
- USB drive = your machine's folder (/home/pettop/data)
- Computer = Docker container
- Files on USB persist after computer restarts

===================================
addgroup -g 82 -S www-data 2>/dev/null || true

Creates a group called www-data
-g 82 = group ID 82 (standard for web servers)
-S = system group (not for login users)
2>/dev/null = silence errors if group already exists
|| true = continue even if it fails (don't crash)
======================================
ls -la ~/data/wordpress/
-------------------------------------

$ docker exec srcs-wordpress-1 ps aux | grep php-fpm
    1 root      0:00 {php-fpm8} php-fpm: master process (/etc/php8/php-fpm.conf)
   13 nobody    0:00 {php-fpm8} php-fpm: pool www
   14 nobody    0:00 {php-fpm8} php-fpm: pool www
   ----------------------------------------------
PHP-FPM = PHP FastCGI Process Manager

It's a PHP application server that runs PHP code and returns results to web servers.
Browser
   ↓
Nginx (web server) - listens on port 80/443
   ↓
PHP-FPM (app server) - listens on port 9000
   ↓
PHP code executes
   ↓
Returns HTML to Nginx
   ↓
Browser displays page
-----------------------------------------------
Nginx = handles HTTP requests, serves static files (images, CSS, JS)
PHP-FPM = executes PHP code, interacts with database
They communicate via port 9000 (TCP connection)
Why separate?
Nginx is fast at serving static content
PHP runs in separate process (if PHP crashes, Nginx still works)
Can scale independently (multiple PHP-FPM processes)
-------------------------------------------------------

WordPress in Docker - Complete Tutorial
What is WordPress?
CMS (Content Management System) - website builder
Manage blog posts, pages, users, plugins, themes
Data stored in database (MariaDB)
Runs on PHP

Nginx (Port 443)          → Serves HTML/CSS/JS
    ↓
PHP-FPM (Port 9000)       → Executes PHP code
    ↓
MariaDB (Port 3306)       → Stores database
    ↓
Volumes                   → Persists data on your machine

tep-by-Step Installation (What You've Done)
1. MariaDB Container - Database

Stores posts, users, settings
Starts automatically with entrypoint script
2. PHP-FPM Container - Application Server

Executes WordPress PHP code
Downloads/installs WordPress on first startup
Stores files in /var/www/html volume
3. Nginx Container - Web Server

Listens on port 443 (HTTPS)
Routes .php requests to PHP-FPM
Serves static files (images, CSS)
4. Volumes - Persistent Storage

~/data/wordpress/ = WordPress files on your host
~/data/mariadb/ = Database files on your host
Survives container restarts