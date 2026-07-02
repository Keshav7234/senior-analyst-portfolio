# Senior Analyst Portfolio - Java Backend

## Overview
This is a full-stack Java Spring Boot application for the Senior Infrastructure Analyst portfolio website.

## Technology Stack
- **Framework**: Spring Boot 3.1.5
- **Language**: Java 17
- **Database**: H2 (In-memory)
- **Build Tool**: Maven
- **Template Engine**: Thymeleaf
- **ORM**: JPA/Hibernate

## Project Structure
```
backend/
├── src/main/java/com/portfolio/
│   ├── PortfolioApplication.java       # Main application entry point
│   ├── controller/
│   │   └── PortfolioController.java    # REST & MVC controllers
│   ├── model/
│   │   ├── Project.java                # Project entity
│   │   ├── Expertise.java              # Expertise entity
│   │   └── ContactMessage.java         # Contact message entity
│   ├── repository/
│   │   ├── ProjectRepository.java      # Project data access
│   │   ├── ExpertiseRepository.java    # Expertise data access
│   │   └── ContactMessageRepository.java # Message data access
│   ├── service/
│   │   └── PortfolioService.java       # Business logic
│   └── config/
│       └── DataInitializer.java        # Database initialization
├── resources/
│   ├── templates/                      # Thymeleaf templates
│   ├── static/                         # CSS, JS, images
│   └── application.properties          # Configuration
└── pom.xml                             # Maven dependencies
```

## Key Features

### Entities
1. **Project** - Contains project details, tags, gradient colors, and user impact metrics
2. **Expertise** - Lists technical expertise with descriptions and icons
3. **ContactMessage** - Stores contact form submissions

### API Endpoints
- `GET /` - Home page with all portfolio data
- `GET /api/projects` - Get all projects (JSON)
- `GET /api/expertise` - Get all expertise (JSON)
- `POST /api/contact` - Submit contact message
- `GET /about` - About page
- `GET /projects` - Projects page

## Running the Application

### Prerequisites
- Java 17 or higher
- Maven 3.6+

### Build
```bash
cd backend
mvn clean package
```

### Run
```bash
mvn spring-boot:run
```

The application will start on `http://localhost:8080`

### Access Points
- **Home**: http://localhost:8080/
- **H2 Console**: http://localhost:8080/h2-console
- **API Projects**: http://localhost:8080/api/projects
- **API Expertise**: http://localhost:8080/api/expertise

## Database
The application uses H2 in-memory database which is automatically initialized with sample data on startup via `DataInitializer.java`.

### Data Initialization
- 6 Sample Projects
- 6 Expertise Areas
- All configured with appropriate icons, colors, and descriptions

## Customization

### Add New Project
```java
Project p = new Project();
p.setTitle("Your Project Title");
p.setDescription("Your description");
p.setTags(Arrays.asList("tag1", "tag2"));
p.setProjectType("Active Directory");
projectRepository.save(p);
```

### Add New Expertise
```java
Expertise e = new Expertise();
e.setTitle("Your Expertise");
e.setDescription("Description");
e.setIcon("fas fa-icon-name");
e.setCardColor("card-blue");
expertiseRepository.save(e);
```

## Frontend Integration
The Thymeleaf templates render the backend data dynamically:
- Projects are displayed with corresponding gradient backgrounds
- Expertise cards are colored based on card-color attribute
- Contact form submits to `/api/contact` endpoint

## Configuration
Edit `application.properties` to customize:
- Server port (default: 8080)
- Database settings
- Logging levels
- Thymeleaf settings

## Dependencies
- **Spring Boot Starter Web** - REST APIs and MVC
- **Spring Boot Starter Thymeleaf** - Template rendering
- **Spring Boot Starter Data JPA** - Database abstraction
- **H2 Database** - In-memory database
- **Lombok** - Reduce boilerplate code
- **Spring Boot DevTools** - Hot reload during development

## Testing
```bash
mvn test
```

## Deployment
The application can be deployed as a standalone JAR:
```bash
java -jar target/senior-analyst-portfolio-1.0.0.jar
```

## Production Considerations
1. Replace H2 with PostgreSQL/MySQL
2. Add authentication/authorization
3. Implement email sending for contact messages
4. Add caching layer (Redis)
5. Setup API rate limiting
6. Add request validation
7. Implement error handling
8. Setup logging framework (SLF4J)

## License
MIT License