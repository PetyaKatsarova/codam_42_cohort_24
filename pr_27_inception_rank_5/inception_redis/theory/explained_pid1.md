PID 1 = Process ID 1 = The first process that runs in a containerWhy it matters:

PID 1 receives all signals (SIGTERM, SIGINT, SIGKILL)
When PID 1 exits, the container stops
PID 1 must handle child process cleanup (zombie processes)
Wrong PID 1 = broken signal handling = container won't stop gracefully

# Check MariaDB
docker exec mariadb ps aux
# Look at first line - PID should be 1

# Check WordPress
docker exec wordpress ps aux
# Look at first line - PID should be 1

# Check Nginx
docker exec nginx ps aux
# Look at first line - PID should be 1

# Or use this one-liner
docker exec mariadb ps -p 1 -o pid,comm,args
docker exec wordpress ps -p 1 -o pid,comm,args
docker exec nginx ps -p 1 -o pid,comm,args
```

### Expected Output (CORRECT)
```
# MariaDB
PID   COMMAND          ARGS
1     mysqld           mysqld --user=mysql --bind-address=0.0.0.0

# WordPress
PID   COMMAND          ARGS
1     php-fpm83        php-fpm: master process

# Nginx
PID   COMMAND          ARGS
1     nginx            nginx: master process
```

### Bad Output (WRONG)
```
PID   COMMAND          ARGS
1     sh               /entrypoint.sh
----------------------------------
The Problem: Shell as PID 1
Bad Dockerfile Pattern
dockerfile# WRONG - Shell becomes PID 1
ENTRYPOINT ["/entrypoint.sh"]
If entrypoint.sh contains:
bash#!/bin/sh
mysqld --user=mysql
```

**Process tree:**
```
PID 1: sh /entrypoint.sh    ← Shell is PID 1 (BAD)
  └─ PID 123: mysqld         ← Actual server
Problems:

Docker sends SIGTERM to PID 1 (shell)
Shell doesn't forward signal to mysqld
Container takes 10 seconds to stop (timeout + SIGKILL)
No graceful shutdown
------------------------------

Test Graceful Shutdown
bash# Start containers
make

# Check PID 1 is correct
docker exec mariadb ps -p 1

# Stop container (sends SIGTERM)
time docker stop mariadb
# Should take ~1-2 seconds (graceful)

# If it takes 10 seconds = WRONG (timeout + SIGKILL)
-----------------------------

Test in Detail
bash# Terminal 1: Watch MariaDB logs
docker logs -f mariadb

# Terminal 2: Stop container
docker stop mariadb

# Logs should show:
# [Note] mysqld: Shutdown complete
# This means it received SIGTERM and shut down gracefully
-----------------------------

Check All Containers
bash# Function to check PID 1
check_pid1() {
    container=$1
    echo "=== $container ==="
    docker exec $container ps -p 1 -o pid,comm,args
    echo ""
}

# Check all
check_pid1 mariadb
check_pid1 wordpress
check_pid1 nginx
```

### Expected Results
```
=== mariadb ===
PID   COMM     ARGS
1     mysqld   mysqld --user=mysql --bind-address=0.0.0.0 --port=3306

=== wordpress ===
PID   COMM        ARGS
1     php-fpm83   php-fpm: master process (/etc/php83/php-fpm.conf)

=== nginx ===
PID   COMM    ARGS
1     nginx   nginx: master process nginx -g daemon off;
-------------------------------

Advanced: Check Process Tree
bash# See full process tree
docker exec mariadb ps auxf

# Or with pstree (if installed)
docker exec mariadb apk add --no-cache pstree
docker exec mariadb pstree -p 1
```

**Good output:**
```
mysqld(1)
```

**Bad output:**
```
sh(1)───mysqld(123)
Zombie Process Check
bash# Check for zombie processes
docker exec mariadb ps aux | grep defunct
docker exec wordpress ps aux | grep defunct
docker exec nginx ps aux | grep defunct

# Should show nothing
# If you see <defunct>, PID 1 isn't reaping children
Summary Checklist
bash# 1. Check PID 1 is the main server process
docker exec mariadb ps -p 1 | grep mysqld
docker exec wordpress ps -p 1 | grep php-fpm
docker exec nginx ps -p 1 | grep nginx

# 2. Check entrypoint uses exec
grep "exec" srcs/requirements/mariadb/tools/entrypoint.sh | tail -1
grep "exec" srcs/requirements/wordpress/tools/entrypoint.sh | tail -1

# 3. Test graceful shutdown
time docker stop mariadb
# Should be < 5 seconds

# 4. Check no zombies
docker exec mariadb ps aux | grep -c defunct
# Should be 0