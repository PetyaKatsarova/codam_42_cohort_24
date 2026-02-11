A volume is a bridge between your host machine and a Docker container that lets them share files and persist data.

Your Machine (Host)           Docker Container
/home/pettop/data/wordpress ←→ /var/www/html
     (real folder)               (container path)

Both point to the SAME files, just different paths.
------------------------
volumes:
  wp:
    driver: local
    driver_opts:
      type: none
      o: bind
      device: /home/${USER}/data/wordpress

wp: = volume name (used by services)
driver: local = use local files (your machine, not cloud)
type: none = direct bind mount (no special processing)
o: bind = bind mount (connect folders)
device: /home/${USER}/data/wordpress = actual folder on your machine

----------------------------
Use in service:
wordpress:
  volumes:
    - wp:/var/www/html
      ↑    ↑
    volume  container path
    name

When WordPress container starts
It mounts volume wp at /var/www/html
Anything written to /var/www/html inside container → goes to wordpress on host


# Inside WordPress container
echo "Hello" > /var/www/html/test.txt
# Your terminal
cat ~/data/wordpress/test.txt
# Output: Hello
Same file, two locations!
=================================
# Start containers
docker-compose up

# You create posts in WordPress admin
# Files go to ~/data/wordpress/wp-content/uploads/
# Posts go to ~/data/mariadb/wordpress/wp_posts

docker-compose down

# Containers deleted, but data remains:
ls ~/data/
# mariadb/    (all posts, users, comments)
# wordpress/  (all images, themes, plugins)

# Start completely NEW containers
docker-compose up

# New containers mount old volumes
# Website appears exactly as it was
# All posts still there
# All images still there
# All users still there

# Backup your data (on your machine)
cp -r ~/data/wordpress~ ~/backups/wordpress-backup-2026-02-07
cp -r ~/data/mariadb ~/backups/mariadb-backup-2026-02-07

# If container corrupts, restore from backup:
rm -rf ~/data/wordpress
cp -r ~/backups/wordpress-backup-2026-02-07 ~/data/wordpress

docker-compose down -v
Container deleted
Volume deleted: ~/data/wordpress/ completely removed
All files gone forever (unless you have backup)

docker volume rm wp
Volume deleted
For bind mounts (your setup): Folder still exists on host
For named volumes: Docker-managed folder deleted
This command only removes Docker's volume metadata, not the actual folder (Docker is being safe)
============================
docker compose up -d

Reads docker-compose.yml
Sees volume definition wp:
Checks if folder exists: wordpress
If not exists → creates it
If exists → uses it as-is
Mounts it into container at /var/www/html
===============================
**Volume** is not a file. It's a config/reference.
Volume = Pointer/Link/Connection
  ↓
Points to: Actual folder (/home/pettop/data/wordpress/)
  ↓
Folder contains: Real files (index.php, wp-config.php, etc.)

3 parts:

    Part	            Type	            Location
Volume definition	Configuration	In docker-compose.yml
Docker metadata	    Config file 	/var/lib/docker/volumes/
Actual files	    Real files	   Your folder (/home/pettop/data/wordpress/)

docker-compose.yml says:
"Call it 'wp', and point to /home/pettop/data/wordpress/"

Container reads this and says:
"Put /home/pettop/data/wordpress/ at /var/www/html"

User sees:
Files in ~/data/wordpress/ appear as ~/data/wordpress/ (same files!)

