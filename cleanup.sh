#!/bin/bash

echo "Cleaning up containers and images..."

# Stop and remove containers
docker-compose down --volumes

# Remove dangling images
docker image prune -f

# Remove dangling volumes
docker volume prune -f

echo "Cleanup complete!"
