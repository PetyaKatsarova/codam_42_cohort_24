In Linux

Every process has a PID (Process ID).

PID 1 = the first process started by the kernel

On a normal Linux system → PID 1 is systemd (or init)

PID 1 is responsible for:

Reaping zombie processes

Forwarding signals

Acting as parent of orphan processes

In a container:

The process you start becomes PID 1 inside that container.

Example:

CMD ["nginx", "-g", "daemon off;"]


Inside the container:

nginx = PID 1


There is no systemd.
================================
Why PID 1 is Special in Docker

PID 1 behaves differently:

1️⃣ Signal handling is broken by default

When you run:

docker stop container


Docker sends:

SIGTERM


If your PID 1 process doesn't handle SIGTERM correctly:

Container doesn't shut down properly
Processes hang
You get zombie processes
=========================
How to TEST PID 1 signal handling (real test):
docker stop wordpress
docker exec -it wordpress ps -o pid,comm

docker exec -it mariadb ps -o pid,comm
docker exec -it nginx ps -o pid,comm
docker exec -it wordpress ps -o pid,comm


PID   COMMAND
    1 entrypoint.sh
    7 mysqld_safe
   74 mariadbd
  500 ps

PID 1 is entrypoint.sh → BAD
mysqld_safe and mariadbd are children
SIGTERM goes to the shell, not to MariaDB

This is exactly the PID 1 problem.
==========================
docker exec -it mariadb ps -o pid,comm
Expected:
PID  COMMAND
1    mysqld
-----------------------------------
docker ps -q | xargs -I {} sh -c 'echo "Container {}:"; docker top {} -o pid,comm | head -n 2'


PID 1 is your shell script (entrypoint.sh) in WordPress and MariaDB containers.

Problem: docker stop sends SIGTERM to PID 1. Your shell script does not forward the signal to php-fpm (WordPress) or mysqld_safe/mariadbd (MariaDB).

Consequence: The main services may not shut down cleanly, risking data corruption.

How to fix it

The idea: replace the shell (PID 1) with the real process using exec, so it becomes PID 1 and receives signals directly.