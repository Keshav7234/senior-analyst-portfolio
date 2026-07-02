#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}================================${NC}"
echo -e "${GREEN}Portfolio Deployment Script${NC}"
echo -e "${GREEN}================================${NC}\n"

# Check if Docker is installed
if ! command -v docker &> /dev/null; then
    echo -e "${RED}Docker is not installed. Please install Docker first.${NC}"
    exit 1
fi

if ! command -v docker-compose &> /dev/null; then
    echo -e "${RED}Docker Compose is not installed. Please install Docker Compose first.${NC}"
    exit 1
fi

echo -e "${YELLOW}✓ Docker and Docker Compose are installed${NC}\n"

# Stop existing containers
echo -e "${YELLOW}Stopping existing containers...${NC}"
docker-compose down 2>/dev/null || true

# Build and start services
echo -e "${YELLOW}Building Docker images...${NC}"
docker-compose build --no-cache

if [ $? -ne 0 ]; then
    echo -e "${RED}Build failed!${NC}"
    exit 1
fi

echo -e "${YELLOW}Starting services...${NC}"
docker-compose up -d

if [ $? -ne 0 ]; then
    echo -e "${RED}Failed to start services!${NC}"
    exit 1
fi

# Wait for services to be ready
echo -e "${YELLOW}Waiting for services to start...${NC}"
sleep 10

# Check service status
echo -e "${YELLOW}Checking service status...${NC}"

# Check C++ Backend
if curl -s http://localhost:8080/api/health > /dev/null; then
    echo -e "${GREEN}✓ C++ Backend is running on port 8080${NC}"
else
    echo -e "${RED}✗ C++ Backend failed to start${NC}"
fi

# Check Frontend
if curl -s http://localhost:3000 > /dev/null; then
    echo -e "${GREEN}✓ Frontend is running on port 3000${NC}"
else
    echo -e "${RED}✗ Frontend failed to start${NC}"
fi

# Check Reverse Proxy
if curl -s http://localhost/health > /dev/null; then
    echo -e "${GREEN}✓ Nginx Reverse Proxy is running on port 80${NC}"
else
    echo -e "${RED}✗ Nginx Reverse Proxy failed to start${NC}"
fi

echo -e "\n${GREEN}================================${NC}"
echo -e "${GREEN}Deployment Complete!${NC}"
echo -e "${GREEN}================================${NC}\n"

echo -e "${YELLOW}Access Points:${NC}"
echo -e "  ${GREEN}Frontend:${NC}       http://localhost:3000"
echo -e "  ${GREEN}C++ API:${NC}        http://localhost:8080/api"
echo -e "  ${GREEN}Reverse Proxy:${NC}   http://localhost"
echo -e "  ${GREEN}Health Check:${NC}    http://localhost/health\n"

echo -e "${YELLOW}Useful Commands:${NC}"
echo -e "  View logs:        ${GREEN}docker-compose logs -f${NC}"
echo -e "  Stop services:    ${GREEN}docker-compose down${NC}"
echo -e "  View containers:  ${GREEN}docker ps${NC}\n"
