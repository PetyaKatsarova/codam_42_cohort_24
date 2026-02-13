# Inception

*This project has been created as part of the 42 curriculum by pekatsar.*

## Description

Inception is a system administration project that focuses on containerization using Docker. The goal is to set up a small infrastructure composed of different services following specific rules. The project involves creating a complete LEMP stack (Linux, Nginx, MariaDB, PHP) using Docker containers, with each service running in its own dedicated container.

The infrastructure must be set up using Docker Compose, with custom Dockerfiles for each service. All containers must be built from either Alpine Linux or Debian base images (penultimate stable version), and the entire setup must be configured to work together seamlessly through Docker networks and volumes.

## Instructions

### Prerequisites

- Docker and Docker Compose installed
- Make utility
- At least 2GB of free disk space
- Sudo privileges (for volume directory creation)

### Installation & Setup

1. **Clone the repository:**
   ```bash
   git clone <repository-url>
   cd inception
   ```

2. **Configure environment variables:**
   - Edit `srcs/.env` with your credentials
   - Update domain name to match your login (e.g., `pekatsar.42.fr`)

3. **Set up hosts file (on your local machine):**
   ```bash
   sudo nano /etc/hosts
   ```
   Add the line:
   ```
   127.0.0.1    pekatsar.42.fr
   ```
   (Replace `pekatsar` with your login)

4. **Build and run:**
   ```bash
   make all
   ```

### Usage

**Start the infrastructure:**
```bash
make up
```

**Stop the infrastructure:**
```bash
make down
```

**Clean everything (including volumes):**
```bash
make fclean
```

**Rebuild from scratch:**
```bash
make re
```

**Access the website:**
- In browser: `https://pekatsar.42.fr:8443` (or `https://localhost:8443` if hosts file not configured)
- Accept the self-signed SSL certificate warning

### Port Forwarding (for VM setup)

If running in a VirtualBox VM, configure port forwarding:
- Protocol: TCP
- Host Port: 8443
- Guest Port: 443

## Project Structure

```
inception/
├── Makefile
├── srcs/
│   ├── docker-compose.yml
│   ├── .env
│   ├── requirements/
│   │   ├── mariadb/
│   │   │   ├── Dockerfile
│   │   │   ├── conf/
│   │   │   └── tools/
│   │   ├── nginx/
│   │   │   ├── Dockerfile
│   │   │   ├── conf/
│   │   │   └── tools/
│   │   └── wordpress/
│   │       ├── Dockerfile
│   │       ├── conf/
│   │       └── tools/
│   └── secrets/
│       ├── db_password.txt
│       └── db_root_password.txt
└── README.md
```

## Technical Overview

### Docker Architecture

The project uses three main containers:

1. **MariaDB Container**
   - Base image: Alpine Linux 3.21
   - Stores WordPress database
   - Exposed only to Docker network (not to host)
   - Uses Docker volumes for data persistence

2. **WordPress Container**
   - Base image: Alpine Linux 3.21
   - Runs PHP-FPM on port 9000
   - Processes PHP requests from Nginx
   - Connects to MariaDB for database operations

3. **Nginx Container**
   - Base image: Alpine Linux 3.21
   - Acts as reverse proxy and web server
   - Handles TLS/SSL encryption (TLSv1.2 and TLSv1.3)
   - Exposed to host on port 443
   - Forwards PHP requests to WordPress container

### Key Design Choices

**Why Alpine Linux?**
- Minimal attack surface (security)
- Small image size (~5MB base vs ~120MB for Debian)
- Faster build and deployment times
- Lower resource consumption

**Container Communication:**
- All containers communicate through a custom Docker bridge network
- Services reference each other by container name (DNS resolution)
- No need for IP addresses or external networking

**Data Persistence:**
- Docker volumes ensure data survives container restarts
- Bind mounts link host directories to container paths
- Separate volumes for database and WordPress files

**Why Docker for this project?**
- Lightweight and fast deployment
- Easy to replicate across different environments
- Perfect for microservices architecture
- Simplified dependency management

**This project uses:**
- **Docker Secrets** for database passwords (more secure)
- **Environment Variables** for non-sensitive config (domain names, usernames)

**Why Secrets for passwords?**
- Not exposed in `docker inspect` output
- Not logged in container logs
- Mounted as read-only files in `/run/secrets/`
- Better security compliance

### Docker Network vs Host Network

| Feature | Docker Network (Bridge) | Host Network |
|---------|------------------------|--------------|
| **Isolation** | Containers isolated from host | Containers use host network directly |
| **Port Mapping** | Required (port forwarding) | Not needed (direct access) |
| **Security** | Better (network separation) | Lower (full host network access) |
| **DNS** | Built-in (container names) | Relies on host DNS |
| **Performance** | Slight overhead (NAT) | Faster (no translation) |

**This project uses Docker Bridge Network:**
- Better security isolation
- Container name-based DNS (nginx → wordpress → mariadb)
- Explicit port exposure control
- Easier to manage and debug

### Docker Volumes vs Bind Mounts

| Feature | Docker Volumes | Bind Mounts |
|---------|---------------|-------------|
| **Management** | Managed by Docker | Managed by user |
| **Location** | `/var/lib/docker/volumes/` | Any host path |
| **Portability** | Better (Docker-aware) | Lower (host-specific paths) |
| **Performance** | Optimized by Docker | Direct filesystem |
| **Backup** | Docker commands | Standard tools |
| **Permissions** | Docker handles | Must configure manually |

**This project uses Bind Mounts:**
- Explicit control over data location (`/home/pekatsar/data/`)
- Easier to backup and inspect
- Required by project subject
- Persistent across Docker system cleanups

**Implementation:**
```yaml
volumes:
  db:
    driver: local
    driver_opts:
      type: none
      o: bind
      device: /home/pekatsar/data/mariadb
```

## Resources

### Documentation
- [Docker Documentation](https://docs.docker.com/)
- [Docker Compose Reference](https://docs.docker.com/compose/compose-file/)
- [Nginx Documentation](https://nginx.org/en/docs/)
- [MariaDB Documentation](https://mariadb.org/documentation/)
- [WordPress Developer Resources](https://developer.wordpress.org/)
- [Alpine Linux Wiki](https://wiki.alpinelinux.org/)

### Tutorials & Articles
- [Docker Networking Deep Dive](https://docs.docker.com/network/)
- [SSL/TLS Configuration Best Practices](https://wiki.mozilla.org/Security/Server_Side_TLS)
- [PHP-FPM with Nginx](https://www.nginx.com/resources/wiki/start/topics/examples/phpfcgi/)
- [Docker Secrets Management](https://docs.docker.com/engine/swarm/secrets/)

### AI Usage in This Project

**Tasks where AI was used:**
1. **Dockerfile optimization** - AI helped identify best practices for multi-stage builds and layer caching
2. **Nginx configuration** - AI assisted in configuring SSL/TLS settings and FastCGI parameters
3. **Troubleshooting** - AI helped debug port forwarding issues between VM and host
4. **Documentation** - AI assisted in structuring this README and explaining technical concepts
5. **Shell scripting** - AI helped create entrypoint scripts for container initialization

**Parts created with AI assistance:**
- Healthcheck configurations in docker-compose.yml
- Makefile automation rules
- Nginx SSL certificate generation script
- WordPress wp-config.php auto-configuration
- MariaDB initialization script

**Parts created independently:**
- Overall architecture design
- Network topology decisions
- Volume mount configuration
- Security decisions (secrets vs env vars)
- Project structure organization

## Troubleshooting

### Common Issues

**1. Port 443 connection refused:**
- Check VirtualBox port forwarding (Host: 8443 → Guest: 443)
- Verify containers are running: `docker ps`
- Check nginx logs: `docker logs nginx`

**2. Database connection failed:**
- Ensure MariaDB is healthy: `docker ps` (check STATUS column)
- Verify secrets are mounted: `docker exec mariadb ls /run/secrets/`
- Check network connectivity: `docker exec wordpress ping mariadb`

**3. Permission denied on volumes:**
- Ensure data directories exist: `ls -la ~/data/`
- Check ownership: `ls -ld ~/data/mariadb ~/data/wordpress`
- Run `make fclean && make all` to recreate

**4. SSL certificate errors:**
- This is expected with self-signed certificates
- Click "Advanced" → "Proceed to localhost (unsafe)" in browser
- For production, use Let's Encrypt

## Project Validation

**Requirements checklist:**
- Docker Compose infrastructure
- Custom Dockerfiles (no pre-built images from DockerHub except base OS)
- Alpine Linux 3.21 (penultimate stable version)
- Nginx with TLSv1.2/TLSv1.3 only
- WordPress + PHP-FPM
- MariaDB
- Volumes for database and website files
- Docker network for inter-container communication
- Containers restart on crash
- Domain name configuration
- No passwords in Dockerfiles
- Environment variables and secrets properly used

## Author

**pekatsar** - 42 Student
- Project: Inception (Rank 5)
- School: 42 Network
- Year: 2026

## License

This project is part of the 42 school curriculum and follows the school's academic policies.
