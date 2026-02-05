#!/bin/sh

set -e

echo "[WordPress] Starting PHP-FPM..."
exec php-fpm -F
