#!/bin/bash
set -e

echo "Setting up Docker permissions and volumes..."
# Check if docker is installed
if ! command -v docker &> /dev/null; then
    echo "Docker is not installed"
    exit 1
fi

echo "Starting docker\n"
# start running docker
sudo dockerd &

# Check if user already in docker group
if groups "$USER" | grep -q docker; then
    echo "✓ $USER already in docker group"
else
    echo "Adding $USER to docker group (requires sudo)..."
    sudo groupadd docker 2>/dev/null || true
    sudo usermod -aG docker "$USER"
    echo "User added - must log out/in or run: newgrp docker"
fi

# Check if docker daemon is running
echo "Checking Docker daemon..."
if docker ps &> /dev/null; then
    echo "✓ Docker daemon is running"
else
    echo "Starting Docker daemon..."
    
    # Try different methods to start docker
    if command -v systemctl &> /dev/null; then
        sudo systemctl start docker 2>/dev/null || echo "systemctl not available (non-systemd system)"
    # elif command -v service &> /dev/null; then
    #     sudo service docker start 2>/dev/null || echo "service command failed"
    elif command -v dockerd &> /dev/null; then
        sudo dockerd > /dev/null 2>&1 & 
        sleep 2
        echo "Started dockerd in background - may need manual restart"
    else
        echo "Could not find docker startup method"
    fi
    
    # Verify docker is now running
    if docker ps &> /dev/null; then
        echo "✓ Docker daemon started successfully"
    else
        echo "Docker daemon still not responding - try: sudo docker system prune"
    fi
fi

# Create and validate volumes
echo ""
echo "Creating volume directories..."
VOLUME_DIR="$HOME/data"

if mkdir -p "$VOLUME_DIR"/{mariadb,wordpress}; then
    echo "✓ Volume directories created:"
    ls -ld "$VOLUME_DIR"/mariadb "$VOLUME_DIR"/wordpress
else
    echo "Failed to create volume directories"
    exit 1
fi

# Add hostname to /etc/hosts
if ! grep -q "inception.42.fr" /etc/hosts; then
    echo "Adding inception.42.fr to /etc/hosts..."
    echo "127.0.0.1 inception.42.fr" | sudo tee -a /etc/hosts > /dev/null
fi

echo ""
echo "✓ Setup complete!"
echo ""
echo "Next steps:"
echo "1. Log out and back in (or run: newgrp docker)"
echo "2. Run: make all"