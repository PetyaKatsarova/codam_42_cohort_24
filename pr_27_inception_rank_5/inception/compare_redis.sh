#!/bin/bash

echo "=== Redis Performance Comparison ==="
echo ""

# Test 1: WITH Redis
echo "1. Testing WITH Redis enabled..."
docker exec wordpress wp redis enable --allow-root > /dev/null 2>&1
sleep 2

echo "   Warming up cache (first request)..."
curl -sk https://pekatsar.42.fr > /dev/null

echo "   Testing 5 requests (using cache):"
for i in {1..5}; do
    TIME=$( { time curl -sk https://pekatsar.42.fr > /dev/null; } 2>&1 | grep real | awk '{print $2}')
    echo "   Request $i: $TIME"
done

# Calculate cache stats
HITS=$(docker exec redis redis-cli INFO stats | grep keyspace_hits | cut -d: -f2 | tr -d '\r')
MISSES=$(docker exec redis redis-cli INFO stats | grep keyspace_misses | cut -d: -f2 | tr -d '\r')
echo "   Cache hits: $HITS, misses: $MISSES"

echo ""
echo "2. Testing WITHOUT Redis (disabled)..."
docker exec wordpress wp redis disable --allow-root > /dev/null 2>&1
docker exec redis redis-cli FLUSHALL > /dev/null 2>&1
sleep 2

echo "   Testing 5 requests (no cache):"
for i in {1..5}; do
    TIME=$( { time curl -sk https://pekatsar.42.fr > /dev/null; } 2>&1 | grep real | awk '{print $2}')
    echo "   Request $i: $TIME"
done

# Re-enable Redis
echo ""
echo "3. Re-enabling Redis..."
docker exec wordpress wp redis enable --allow-root > /dev/null 2>&1

echo ""
echo "✓ Comparison complete!"
echo "Expected: Requests WITH Redis are 2-3x faster"