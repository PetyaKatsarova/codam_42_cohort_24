#!/bin/sh

set -e

echo "[WordPress] Waiting for MariaDB to be ready..."
while ! nc -z mariadb 5306; do
    echo "Waiting for mariadb:5306..."
    sleep 1
done

echo "[WordPress] MariaDB is ready!"

echo "[WordPress] Waiting for Redis to be ready..."
while ! nc -z redis 6379; do
    echo "Waiting for redis:6379..."
    sleep 1
done

echo "[WordPress] Redis is ready!"

echo "[WordPress] Checking for WordPress files..."
if [ ! -f /var/www/html/wp-load.php ]; then
    echo "[WordPress] Downloading and extracting WordPress..."
    curl -L https://wordpress.org/latest.tar.gz | tar xz --strip-components=1 -C /var/www/html
    echo "[WordPress] WordPress downloaded successfully"
fi

echo "[WordPress] Setting permissions..."
chown -R www-data:www-data /var/www/html

# Read database password from secrets
DB_PASSWORD=$(cat /run/secrets/db_password)
WP_ADMIN_PASSWORD=$(cat /run/secrets/wp_admin_password)
WP_USER_PASSWORD=$(cat /run/secrets/wp_user_password)

# Create wp-config.php if it doesn't exist
if [ ! -f /var/www/html/wp-config.php ]; then
    echo "[WordPress] Creating wp-config.php..."
    wp config create \
        --dbname="${MYSQL_DATABASE}" \
        --dbuser="${MYSQL_USER}" \
        --dbpass="${DB_PASSWORD}" \
        --dbhost="${DB_HOST}" \
        --allow-root
    echo "[WordPress] wp-config.php created"
fi

# Install WordPress if not already installed
if ! wp core is-installed --allow-root 2>/dev/null; then
    echo "[WordPress] Installing WordPress..."
    wp core install \
        --url="${DOMAIN_NAME}" \
        --title="${WP_TITLE}" \
        --admin_user="${WP_ADMIN_USER}" \
        --admin_password="${WP_ADMIN_PASSWORD}" \
        --admin_email="${WP_ADMIN_EMAIL}" \
        --allow-root
    echo "[WordPress] WordPress installed successfully"
    
    # Create second user (regular user, not admin)
    echo "[WordPress] Creating second user..."
    wp user create \
        "${WP_USER}" \
        "${WP_USER_EMAIL}" \
        --role=author \
        --user_pass="${WP_USER_PASSWORD}" \
        --allow-root
    echo "[WordPress] Second user created successfully"
else
    echo "[WordPress] WordPress already installed"
fi

echo "[WordPress] Final permission check..."
chown -R www-data:www-data /var/www/html

# Install and enable Redis Object Cache
if ! wp plugin is-installed redis-cache --allow-root 2>/dev/null; then
    echo "[WordPress] Installing Redis Object Cache plugin..."
    wp plugin install redis-cache --activate --allow-root
    wp config set WP_REDIS_HOST redis --allow-root
    wp config set WP_REDIS_PORT 6379 --raw --allow-root
    wp config set WP_CACHE true --raw --allow-root
    
    # Enable Redis cache (requires FLUSHDB command)
    wp redis enable --allow-root || echo "[WordPress] Redis enable failed, will enable manually"
    echo "[WordPress] Redis plugin configured"
else
    echo "[WordPress] Redis cache already installed"
fi

echo "[WordPress] Starting PHP-FPM..."
exec /usr/sbin/php-fpm83 -F