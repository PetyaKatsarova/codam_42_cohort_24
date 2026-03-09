#!/bin/sh
set -e

echo "[WordPress] Waiting for MariaDB..."
while ! nc -z mariadb 3306; do
    sleep 1
done
echo "[WordPress] MariaDB ready!"

echo "[WordPress] Waiting for Redis..."
while ! nc -z redis 6379; do
    sleep 1
done
echo "[WordPress] Redis ready!"

if [ ! -f /var/www/html/wp-load.php ]; then
    echo "[WordPress] Downloading WordPress..."
    curl -L https://wordpress.org/latest.tar.gz | tar xz --strip-components=1 -C /var/www/html
fi

chown -R www-data:www-data /var/www/html

DB_PASSWORD=$(cat /run/secrets/db_password)
WP_ADMIN_PASSWORD=$(cat /run/secrets/wp_admin_password)
WP_USER_PASSWORD=$(cat /run/secrets/wp_user_password)

if [ ! -f /var/www/html/wp-config.php ]; then
    echo "[WordPress] Creating wp-config.php..."
    wp config create \
        --dbname="${MYSQL_DATABASE}" \
        --dbuser="${MYSQL_USER}" \
        --dbpass="${DB_PASSWORD}" \
        --dbhost="${DB_HOST}" \
        --allow-root

    wp config set WP_REDIS_HOST "${WP_REDIS_HOST}" --allow-root
    wp config set WP_REDIS_PORT 6379 --raw --allow-root
    wp config set WP_CACHE true --raw --allow-root
fi

if ! wp core is-installed --allow-root 2>/dev/null; then
    echo "[WordPress] Installing WordPress..."
    wp core install \
        --url="${DOMAIN_NAME}" \
        --title="${WP_TITLE}" \
        --admin_user="${WP_ADMIN_USER}" \
        --admin_password="${WP_ADMIN_PASSWORD}" \
        --admin_email="${WP_ADMIN_EMAIL}" \
        --allow-root

    echo "[WordPress] Installing Redis plugin..."
    wp plugin install redis-cache --activate --allow-root
    wp redis enable --allow-root

    echo "[WordPress] Creating second user..."
    wp user create \
        "${WP_USER}" \
        "${WP_USER_EMAIL}" \
        --role=author \
        --user_pass="${WP_USER_PASSWORD}" \
        --allow-root
fi

chown -R www-data:www-data /var/www/html

echo "[WordPress] Starting PHP-FPM..."
exec /usr/sbin/php-fpm83 -F