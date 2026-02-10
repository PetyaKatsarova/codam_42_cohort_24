To verify they exist inside the container:

docker exec nginx ls -la /etc/nginx/ssl/

Nginx is listening on 0.0.0.0:443 inside the container
Port mapping is 0.0.0.0:8443->443/tcp
curl -k https://localhost:443 fails (expected - you're mapping to 8443)
curl -k https://localhost:8443 gave NO output (this is strange)
nginx is unhealthy
No nginx logs (which is odd - should have access logs at minimum)

echo "127.0.0.1 pekatsar.42.fr" | sudo tee -a /etc/hosts

curl -k https://pekatsar.42.fr:8443
pekatsar@pekatsar2:~/inception$ 
