#!/bin/sh

set -e

echo "[WordPress] Waiting for MariaDB to be ready..."
while ! nc -z mariadb 3306; do
    echo "Waiting for mariadb:3306..."
    sleep 1
done
echo "[WordPress] MariaDB is ready!"

echo "[WordPress] Checking for WordPress files..."
if [ ! -f /var/www/html/wp-load.php ]; then
    echo "[WordPress] Downloading and extracting WordPress..."
    curl -L https://wordpress.org/latest.tar.gz | tar xz --strip-components=1 -C /var/www/html
else
    echo "[WordPress] WordPress already installed"
fi

echo "[WordPress] Setting permissions..."
chown -R www-data:www-data /var/www/html

echo "[WordPress] Starting PHP-FPM..."
exec /usr/sbin/php-fpm8 -F
