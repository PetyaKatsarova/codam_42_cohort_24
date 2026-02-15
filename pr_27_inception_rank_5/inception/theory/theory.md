Flush DNS = Clear the DNS cache (Windows stores domain name lookups in memory).

//Your browser can't resolve pekatsar.42.fr yet because Windows DNS cache still doesn't know about it.
//Open PowerShell as Administrator and run:
ipconfig /flushdns
---------------------------------------
These 3 are built-in networks and recreated automatically. Don't delete them.

bridge    # Default network for containers
host      # Container shares host network
none      # No networking
-----------------------------------------
docker exec mariadb mariadb -uwordpress -p$(cat secrets/db_password.txt) -h mariadb -e "SHOW DATABASES;"
docker exec mariadb mariadb -uroot -p$(cat secrets/db_root_password.txt) -e "USE wordpress; SHOW TABLES;"

Database
information_schema    # System database - metadata about all databases
mysql                 # System database - user accounts, permissions, config
performance_schema    # System database - performance monitoring data
sys                   # System database - performance views (readable format)
wordpress             # YOUR database - WordPress content (posts, users, etc.)


# Show structure of each table
docker exec mariadb mariadb -uroot -p$(cat secrets/db_root_password.txt) -e "USE wordpress; SHOW TABLES;" | tail -n +2 | while read table; do
    echo "=== Table: $table ==="
    docker exec mariadb mariadb -uroot -p$(cat secrets/db_root_password.txt) -e "DESCRIBE wordpress.$table;"
    echo ""
done

# Show users in wp_users table
docker exec mariadb mariadb -uroot -p$(cat secrets/db_root_password.txt) wordpress -e "SELECT ID, user_login, user_email FROM wp_users;"

# Show posts
docker exec mariadb mariadb -uroot -p$(cat secrets/db_root_password.txt) wordpress -e "SELECT ID, post_title, post_status, post_date FROM wp_posts WHERE post_type='post';"

---------------------------------
# quick check of all
docker exec mariadb mariadb -uroot -p$(cat secrets/db_root_password.txt) wordpress -e "SHOW TABLES;" && \
for table in $(docker exec mariadb mariadb -uroot -p$(cat secrets/db_root_password.txt) wordpress -e "SHOW TABLES;" | tail -n +2); do
    echo ""; echo "=== $table ==="; 
    docker exec mariadb mariadb -uroot -p$(cat secrets/db_root_password.txt) wordpress -e "DESCRIBE $table;";
done
----------------------------------
The subject says: "The latest tag is prohibited"
Why You See latest Tag
The latest tag is automatically added by Docker when you don't specify a tag in your docker-compose.yml.
Your docker-compose.yml:
yamlservices:
  mariadb:
    image: mariadb    # ← No tag specified, Docker adds :latest
Docker interprets this as mariadb:latest and tags your built image as latest.