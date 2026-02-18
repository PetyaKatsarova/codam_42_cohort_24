echo "=== Testing Redis Integration ==="

echo "1. Redis ping:"
docker exec redis redis-cli ping

echo ""
echo "2. Enable Redis cache:"
docker exec wordpress wp redis enable --allow-root

echo ""
echo "3. Check status:"
docker exec wordpress wp redis status --allow-root

echo ""
echo "4. Visit site to generate cache:"
curl -sk https://pekatsar.42.fr:8443 > /dev/null

echo ""
echo "5. Check cached keys:"
docker exec redis redis-cli KEYS "*"

echo ""
echo "✓ Done!"