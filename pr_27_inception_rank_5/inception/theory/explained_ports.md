In Docker, the ports section maps a port on your host (your computer or VM) to a port inside the container.
The format is:

"host_port:container_port"

host_port: The port you use to access the service from outside the container (e.g., in your browser).
container_port: The port the service listens to inside the container.


rm -rf ~/.cache/chromium

in docker-compose.yml
ports:
  "443:8443"
  Now, you must access the service at https://localhost:8443.
  -----------------------------

  steps to change guest(container) port:
  1. in docker-compose.yml in nginx services
  ports:
	"443:8443"

 2. in nginx/Dockerfile
	EXPOSE 8443

3. in nginx/conf/nginx.conf
	listen 8443 ssl;
    listen [::]:8443 ssl;

4. in browser type as usual:
	https://localhost  // :443 is by default: no need

// todo: weird bug: localhost is fine but localhost/wp-admin site cant be opened!
// suspect sht with wordpress default settings

------------------------------------------------

Host port 8443: Access from browser at https://localhost:8443
Container port 443: nginx listens on standard 443 internally

ports:
  - "8443:443"  # Host 8443 → Container 443
healthcheck:
  test: ["CMD-SHELL", "wget --spider https://localhost:443 --no-check-certificate || exit 1"]


	

