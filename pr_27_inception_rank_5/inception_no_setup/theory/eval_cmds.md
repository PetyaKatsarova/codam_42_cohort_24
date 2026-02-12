;; prove no nginx in wordpress:
docker exec -it wordpress sh
;;  a(show for all users) u(show user/owner info) x(show processes not attached to terminal)
ps aux
;; show all running processes with details

docker exec -it nginx sh
ps aux

;;  show volume mount location
docker volume inspect inception_db

-------------------------------
;;  prove data persist: -i(interactive: keeps stdin open so u can type inside the container)
;;  -t(pseudo-tty: gives you a terminal inside the container)
;; -it  → interactive terminal session
;;  sh = shell starts a command interpreter inside the container.
;;  most Alpine containers dont have bash, so we use sh
;;  / # this means we r inside the container

docker exec -it mariadb sh
ls /var/lib/mysql
--------------------------------

;;  show tls v: should fail: v1
openssl s_client -connect localhost:443 -tls1

;;  should succeed: v1.3
openssl s_client -connect localhost:443 -tls1_2
openssl s_client -connect localhost:443 -tls1_3
or:
curl -v --tlsv1.2 https://localhost 
curl -v --tlsv1.1 https://localhost

curl -vk https://localhost
--------------------------------


docker ps
docker volume ls
docker volume inspect inception_db
docker volume inspect inception_wp
openssl s_client -connect localhost:443 -tls1
openssl s_client -connect localhost:443 -tls1_2

;; Both named volumes must store their data inside /home/login/data on the host
;; machine. Replace "login" with your learner's username
;; shows all metadata of the container.
docker inspect mariadb | grep Source
docker inspect mariadb | grep Destination


--------------------------------
!!NB!!
tlooks like a bind, but from Docker's perspective it's still a named volume.

driver_opts with type: none and o: bind just tells Docker: “store this named volume at this host path.”

You're not using ephemeral container storage.

The container still sees it as a normal volume (/var/lib/mysql inside MariaDB).

So: bind on host path ≠ bind volume in the usual sense; it's just a named volume stored where you want.



