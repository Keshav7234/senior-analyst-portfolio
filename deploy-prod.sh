#!/bin/bash

# Deploy to production using Docker

echo "Starting production deployment..."

# Pull latest code
git pull origin main

# Build images
docker-compose build --no-cache

# Stop old containers
docker-compose down

# Start new containers
docker-compose up -d

# Run migrations/initialization
docker-compose exec cpp-backend portfolio_server

echo "Deployment complete!"
echo "Access: http://localhost"
