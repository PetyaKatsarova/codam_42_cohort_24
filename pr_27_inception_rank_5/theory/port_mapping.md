Your Browser                    Docker Network              Container
https://localhost:443   ???     How does this reach       Nginx listens on 443
                                Nginx inside docker?
-----------------------------------------------
 Docker needs to bridge the connection using port mapping.
Port Mapping = Connects a port on your machine to a port inside the container
Your Machine (Host)           Docker Container
localhost:443 ←→ 443 (Nginx inside container)
------------------------
In docker-compose.yml, we specify:
services:
  nginx:
    ports:
      - "433:443"
------------------------
This means:
- The first 433 (before the colon) is the port on your machine (host).
- The second 443 (after the colon) is the port inside the container where Nginx is listening.
So when you access https://localhost:433, Docker forwards that request to port 443 inside the Nginx container, allowing you to see your WordPress site.
=====================