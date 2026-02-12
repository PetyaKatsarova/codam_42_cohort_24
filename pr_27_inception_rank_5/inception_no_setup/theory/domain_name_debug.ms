docker exec -it inception_nginx ls /etc/nginx/ssl
//check if ssl certificate was created

// reload nginx inside container:first nginx is container name
docker exec -it nginx nginx -s reload
