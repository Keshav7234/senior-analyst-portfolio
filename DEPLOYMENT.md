# Senior Analyst Portfolio - Complete Stack

## Multi-Language, Multi-Framework Deployment

### Technology Stack

#### Frontend
- HTML5, CSS3, JavaScript
- Responsive design (Mobile, Tablet, Desktop)
- Deployed via Nginx

#### Backend Options
1. **C++ (Primary)**
   - Framework: Crow
   - Database: SQLite3
   - Performance: Ultra-fast, low memory footprint
   - Port: 8080

2. **Java (Alternative)**
   - Framework: Spring Boot 3.1.5
   - Database: H2/MySQL/PostgreSQL
   - Enterprise-ready
   - Port: 8081

#### Infrastructure
- Docker & Docker Compose
- Nginx Reverse Proxy
- Load Balancing
- CORS & Rate Limiting

## Quick Start

### Prerequisites
- Docker
- Docker Compose
- Git

### Deployment

```bash
# Clone repository
git clone https://github.com/Keshav7234/senior-analyst-portfolio.git
cd senior-analyst-portfolio

# Make deploy script executable
chmod +x deploy.sh

# Run deployment
./deploy.sh
```

### Docker Compose Up

```bash
# Start all services
docker-compose up -d

# View logs
docker-compose logs -f

# Stop services
docker-compose down
```

## Access Points

| Service | URL | Port |
|---------|-----|------|
| Frontend | http://localhost:3000 | 3000 |
| C++ API | http://localhost:8080 | 8080 |
| Java API | http://localhost:8081 | 8081 |
| Reverse Proxy | http://localhost | 80 |
| All Services | http://localhost | 80 |

## API Endpoints

### C++ Backend (Crow)
```
GET  /api/projects   - Get all projects
GET  /api/expertise  - Get all expertise
GET  /api/tools      - Get all tools
POST /api/contact    - Submit contact message
GET  /api/health     - Health check
```

### Java Backend (Spring Boot)
```
GET  /api/projects   - Get all projects
GET  /api/expertise  - Get all expertise
POST /api/contact    - Submit contact message
GET  /about          - About page
GET  /projects       - Projects page
```

## Docker Services

### 1. C++ Backend (cpp-backend)
- **Image**: Custom built from Dockerfile
- **Port**: 8080
- **Database**: SQLite (portfolio.db)
- **Volume**: portfolio_db
- **Health Check**: /api/health

### 2. Java Backend (java-backend)
- **Image**: maven:3.8-openjdk-17
- **Port**: 8081
- **Command**: mvn clean spring-boot:run
- **Optional**: Can be disabled in docker-compose.yml

### 3. Frontend (frontend)
- **Image**: Custom Nginx
- **Port**: 3000
- **Content**: HTML, CSS, JavaScript
- **Proxy**: Routes to C++ backend

### 4. Reverse Proxy (reverse-proxy)
- **Image**: nginx:latest
- **Port**: 80, 443
- **Function**: Load balancing, rate limiting, CORS
- **Config**: nginx.conf

## Features

### Security
- ✅ CORS headers configured
- ✅ Rate limiting (API: 10r/s, General: 30r/s)
- ✅ Request size limits (20MB max)
- ✅ Health checks
- ✅ Error handling

### Performance
- ✅ Gzip compression
- ✅ Connection pooling
- ✅ Multi-threaded backends
- ✅ Load balancing
- ✅ Caching headers

### Scalability
- ✅ Containerized architecture
- ✅ Easy horizontal scaling
- ✅ Database persistence
- ✅ Volume mounts for data
- ✅ Network isolation

## Configuration

### Environment Variables

```bash
# C++ Backend
DATABASE_PATH=/app/portfolio.db

# Java Backend
JAVA_OPTS=-Xmx512m -Xms256m

# Frontend
API_URL=http://cpp-backend:8080
```

### Nginx Configuration
- HTTPS ready (certificates required for production)
- Rate limiting zones
- Upstream servers with failover
- CORS headers
- Gzip compression

## Monitoring

### Health Checks
```bash
# C++ Backend
curl http://localhost:8080/api/health

# General health
curl http://localhost/health

# Frontend
curl http://localhost:3000
```

### View Logs
```bash
# All services
docker-compose logs -f

# Specific service
docker-compose logs -f cpp-backend

# Follow only
docker-compose logs -f --tail=50
```

## Deployment Options

### Local Development
```bash
./deploy.sh
```

### Production
```bash
./deploy-prod.sh
```

### Cloud Platforms
- **AWS ECS**: Use docker-compose to generate CloudFormation
- **Google Cloud**: Deploy with Cloud Run
- **Azure**: Use Container Instances
- **DigitalOcean**: App Platform support
- **Heroku**: Deploy using Dockerfile

## Database

### SQLite (C++ Backend)
- File: `portfolio.db`
- Location: `/app/portfolio.db` (Docker volume)
- Pre-populated with 6 projects and 6 expertise areas
- Automatic schema creation

### H2 (Java Backend - Optional)
- In-memory database
- Auto-creates on startup
- Test data seeded automatically

## Scaling

### Horizontal Scaling
```bash
# Increase replicas
docker-compose up -d --scale cpp-backend=3
```

### Load Balancing
Nginx reverse proxy automatically distributes requests

## Troubleshooting

### Container won't start
```bash
# Check logs
docker-compose logs cpp-backend

# Rebuild image
docker-compose build --no-cache
```

### Database connection error
```bash
# Verify volume
docker volume ls

# Inspect volume
docker volume inspect senior-analyst-portfolio_portfolio_db
```

### Port already in use
```bash
# Find process
lsof -i :8080

# Kill process
kill -9 <PID>

# Or change port in docker-compose.yml
```

## Production Checklist

- [ ] SSL/TLS certificates configured
- [ ] Database backups enabled
- [ ] Monitoring and logging setup
- [ ] Rate limiting tuned
- [ ] CORS origins restricted
- [ ] Environment variables secured
- [ ] Health checks verified
- [ ] Load testing performed
- [ ] Documentation updated
- [ ] Team trained

## Contributing

Fork → Create feature branch → Commit → Push → Create PR

## License

MIT License - See LICENSE file

## Support

- **Issues**: GitHub Issues
- **Documentation**: See README files in each backend folder
- **Community**: Discussions section

---

**Built with ❤️ for Enterprise Infrastructure Analysts**
