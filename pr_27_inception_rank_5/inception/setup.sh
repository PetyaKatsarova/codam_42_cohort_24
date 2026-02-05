#!/bin/bash
# Automatic setup script for Inception project
# Sets up Docker permissions and creates required volume directories

set -e

echo "Setting up Docker permissions..."

# Check if already in docker group
if groups $USER | grep -q docker; then
    echo "✓ $USER already in docker group"
else
    # Create docker group if it doesn't exist
    if ! getent group docker > /dev/null 2>&1; then
        echo "Creating docker group..."
        sudo groupadd docker
    fi
    
    echo "Adding $USER to docker group..."
    sudo usermod -aG docker $USER
    echo "✓ User added to docker group (may require re-login to take effect)"
fi

# Try to restart docker if available
if command -v systemctl &> /dev/null; then
    sudo systemctl restart docker 2>/dev/null || true
elif command -v service &> /dev/null; then
    sudo service docker restart 2>/dev/null || true
fi

echo ""
echo "Creating volume directories..."
mkdir -p "$HOME/data/mariadb"
mkdir -p "$HOME/data/wordpress"
echo "Volume directories created at ~/data/"

