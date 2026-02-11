inception/
├── Makefile
├── setup.sh
├── srcs/
│   ├── .env
│   ├── docker-compose.yml
│   └── requirements/
│       ├── mariadb/
│       │   ├── Dockerfile
│       │   ├── conf/
│       │   └── tools/
│       │       └── entrypoint.sh
│       ├── wordpress/
│       │   ├── Dockerfile
│       │   ├── conf/
│       │   │   └── php-fpm.conf
│       │   └── tools/
│       │       └── entrypoint.sh
│       └── nginx/
│           ├── Dockerfile
│           ├── conf/
│           │   └── nginx.conf
│           └── tools/
│               └── entrypoint.sh
---------------------------------------------------
communication flow:
Browser (port 443)
    ↓ HTTPS
Nginx
    ↓ FastCGI (port 9000)
WordPress (PHP-FPM)
    ↓ TCP (port 3306)
MariaDB
------------------------------------------
WORDPRESS DOCKERFILE:
php-fpm = Executes PHP code
php-mysqli = Connect to MariaDB
php-* = WordPress modules
wget = Download WordPress
netcat-openbsd = Health checks
EXPOSE 9000 = Nginx connects here
-------------------------------------------
php-fpm.conf:
Config meanings:
[www] = Pool name (default)
It's a pool name - a group of PHP-FPM processes. You can have multiple pools. [www] is the default/standard name.

Security! PHP-FPM should NOT run as root.
All PHP processes run as the www-data user
www-data has limited permissions (unprivileged)
If hacked, attacker only gets www-data permissions, not full server

 www-data is a standard Linux user:

Created by Docker/Linux for web services
Already exists in Alpine Linux when you install php-fpm
Same concept as nginx user or mysql user

listen = 0.0.0.0:9000 = Nginx connects to this port
user = www-data = Process runs as www-data (unprivileged)
pm = dynamic = Starts 2, scales to 5 if needed
pm.max_requests = 500 = Refresh processes (prevents memory leaks)

[www]
listen = 0.0.0.0:9000
user = www-data           # ← Run as unprivileged www-data user
group = www-data          # ← Same group as user
pm = dynamic              # ← Scales processes based on load
pm.max_children = 5       # ← Max 5 processes
pm.start_servers = 2      # ← Start with 2 processes
pm.min_spare_servers = 1  # ← Keep at least 1 idle
pm.max_spare_servers = 3  # ← Don't keep more than 3 idle
pm.max_requests = 500     # ← Recycle after 500 requests

why dynamic? We don't know WordPress traffic in advance
Scales up when busy (more processes)
Scales down when quiet (less memory)
Perfect for development & production

Initial state:    2 processes running

Request 1 arrives:  Uses process 1
Request 2 arrives:  Uses process 2
Request 3 arrives:  Need new process → Kill idle one, create new → 3 processes
Request 4 arrives:  Need new process → 4 processes
Request 5 arrives:  Need new process → 5 processes (MAX)

Traffic drops:      Idle processes die
                    Back to 1-2 processes
--------------------------------------------
Why pm.max_requests = 500?
Forces PHP to recycle processes every 500 requests to prevent:

Memory leaks
Stale process state
Security issues from long-running processes
-----------------------------------------------
A pool is a group of PHP-FPM worker processes with their own configuration.
-----------------------------------------------
**NB**

Quick Summary:

What entrypoint.sh Does:
Wait for MariaDB - Check if database is ready (60 sec timeout)
Install WordPress - Download from internet if not exists (first run only)
Fix Permissions - Change owner to www-data user
Start PHP-FPM - Begin serving requests in foreground
What Needs Installed:
php-fpm - Runs PHP
php-mysqli - Database connection
php-* modules - WordPress features
wget - Download WordPress
netcat-openbsd - Health checks
Volumes:
Without: WordPress lost on restart, re-downloads each time
With: WordPress persistent, fast restarts, see files on computer
Your setup: ~/data/wordpress ← → /var/www/html
Image:
Image = Blueprint (text recipe in Dockerfile)
Container = Running instance (from image)
Image builds in layers (Alpine → PHP → Config → Entrypoint)
~125MB image size
-------------------------------------------

cd /home/codam_42_cohort_24/pr_27_inception_rank_5/inception
docker-compose -f srcs/docker-compose.yml logs wordpress --tail 30
-------------------------------------------

Volumes explanation:
volumes:
  - wp:/var/www/html

wp = named volume (defined at bottom of docker-compose.yml)
Bound to /home/${USER}/data/wordpress on your machine (host)
Mounted at /var/www/html inside container
Files persist after container stops/restarts
Where to find:

Machine: ~/data/wordpress (same as wordpress)
Container: /var/www/html
Both point to the same files

How to access container:
docker-compose -f srcs/docker-compose.yml exec wordpress sh

FOUND YOUR PROBLEM! Look at the logs:
chown: unknown user/group www-data:www-data

The www-data user doesn't exist in your Alpine container! That's why the entrypoint crashes. Fix it in the Dockerfile:

Done! Added www-data user creation to the Dockerfile. Now try:

The WordPress container should start successfully now that the www-data user exists.
==================================
test: ["CMD", "nc", "-z", "localhost", "9000"]
nc = netcat(network utility)
-z = zero-I/O mode (just check if port is open)
-z = zero-I/O mode (scan for listening daemons without sending data)
localhost = target host
9000 = port number (PHP-FPM default port)

Checks if PHP-FPM is listening on port 9000 inside the WordPress container.

!!NB!!
Service dependency: Your nginx service depends on wordpress with condition: service_healthy (line 50-51)
Prevents premature connections: Without this, nginx might start before PHP-FPM is ready, causing 502 Bad Gateway errors
Orchestration: Docker Compose waits for this healthcheck to succeed before starting dependent services

!!NB!!
MariaDB starts → runs healthcheck every 10s
WordPress waits (line 32-33) until MariaDB is healthy (database accepting connections)
WordPress starts → runs healthcheck every 5s
Nginx waits (line 50-51) until WordPress is healthy (PHP-FPM ready)
Nginx starts → serves requests

depends_on = "Don't start me until X is ready"
healthcheck = "Here's how to tell if I'm actually ready"
Together = Proper service orchestration with readiness guarantees

!!NB!!
_check_docker:
    @docker ps > /dev/null 2>&1 || (echo "Docker not accessible. Run: newgrp docker" && exit 1)
1: @docker ps > /dev/null 2>&1
@ = Don't print the command itself (silent)
docker ps = List running containers (requires Docker daemon access)
> /dev/null = Redirect stdout to trash (discard output)
2>&1 = Redirect stderr to stdout (also to trash)
Result: Runs silently, only exit code matters

Part 2: ||
Logical OR = "If left command fails, run right command"
docker ps succeeds (exit 0) → nothing happens ✅
docker ps fails (exit 1) → run the error message ❌