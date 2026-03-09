#!/bin/bash
set -e

echo "=== Inception Docker Setup Script ==="
echo ""

# Detect if running in WSL
if grep -qi microsoft /proc/version; then
    echo "Detected WSL environment"
    WSL=true
else
    echo "Detected native Linux"
    WSL=false
fi

# Check if running on Debian/Ubuntu
if [ -f /etc/debian_version ]; then
    echo "Detected Debian-based system"
else
    echo "Warning: This script is designed for Debian/Ubuntu"
fi

# Install Docker and Docker Compose if not present
if ! command -v docker &> /dev/null || ! command -v docker-compose &> /dev/null; then
    echo ""
    echo "Installing Docker and Docker Compose..."
    sudo apt update
    sudo apt install -y docker.io docker-compose
    echo "Docker and Docker Compose installed"
else
    echo "Docker and Docker Compose already installed"
fi

# Add user to docker group
echo ""
echo "Configuring Docker permissions..."
if groups "$USER" | grep -q docker; then
    echo "$USER already in docker group"
else
    echo "Adding $USER to docker group..."
    sudo groupadd docker 2>/dev/null || true
    sudo usermod -aG docker "$USER"
    echo "User added to docker group"
    NEED_RELOGIN=true
fi

# Start Docker daemon based on environment
echo ""
echo "Starting Docker daemon..."

if [ "$WSL" = true ]; then
    # WSL - use service or dockerd directly
    if pgrep -x dockerd > /dev/null; then
        echo "Docker daemon already running"
    else
        echo "Starting dockerd for WSL..."
        sudo dockerd > /dev/null 2>&1 &
        sleep 3
    fi
else
    # Native Linux - use systemctl
    sudo systemctl start docker
    sudo systemctl enable docker
    sleep 2
fi

# Verify docker is running
if docker ps &> /dev/null 2>&1; then
    echo "Docker daemon is running"
else
    echo "Docker daemon not responding, trying alternative method..."
    
    # Kill any existing dockerd
    sudo pkill dockerd 2>/dev/null || true
    sleep 1
    
    # Start dockerd manually
    sudo dockerd > /dev/null 2>&1 &
    sleep 4
    
    if docker ps &> /dev/null 2>&1; then
        echo "Docker daemon is running"
    else
        echo "Docker daemon failed to start"
        echo "Try manually: sudo dockerd"
        exit 1
    fi
fi

# Add hostname to /etc/hosts: can substitude pekatsar with ${USER}
echo ""
echo "Configuring hostname..."
HOSTNAME="pekatsar.42.fr"
if grep -q "$HOSTNAME" /etc/hosts; then
    echo "$HOSTNAME already in /etc/hosts"
else
    echo "Adding $HOSTNAME to /etc/hosts..."
    echo "127.0.0.1 $HOSTNAME" | sudo tee -a /etc/hosts > /dev/null
    echo "$HOSTNAME added to /etc/hosts"
fi


# Add hostname to /etc/hosts (if not already present) todo: check if already exists
echo "127.0.0.1 pekatsar.42.fr" | sudo tee -a /etc/hosts

# Summary
echo ""
echo "================================================"
echo "Setup complete!"
echo "================================================"
echo ""
echo "Configuration summary:"
echo "  - Docker version: $(docker --version)"
echo "  - Docker Compose version: $(docker-compose --version)"
echo ""

if [ "$WSL" = true ]; then
    echo "WSL Note: Docker daemon started in background"
    echo "If docker stops working, run: sudo dockerd &"
    echo ""
fi

if [ "$NEED_RELOGIN" = true ]; then
    echo "IMPORTANT: Run 'newgrp docker' or log out and log back in"
    echo ""
fi

echo "Next steps:"
echo "  make        # Build and start all services"
echo ""