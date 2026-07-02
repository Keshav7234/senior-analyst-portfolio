#include "crow_all.h"
#include <memory>
#include <iostream>
#include "include/database.hpp"
#include "include/routes.hpp"
#include "include/middleware.hpp"

int main() {
    std::cout << "\n=== Senior Analyst Portfolio - C++ Backend ===\n" << std::endl;
    std::cout << "Starting server..." << std::endl;

    // Initialize database
    auto db = std::make_shared<portfolio::database::Database>("portfolio.db");
    if (!db->init()) {
        std::cerr << "Failed to initialize database" << std::endl;
        return 1;
    }
    std::cout << "✓ Database initialized" << std::endl;

    // Create Crow app
    crow::SimpleApp app;

    // Setup routes
    portfolio::routes::PortfolioRoutes portfolio_routes(db);
    portfolio_routes.setup(app);

    portfolio::routes::ApiRoutes api_routes(db);
    api_routes.setup(app);

    // Setup middleware
    portfolio::middleware::setup_middlewares(app);

    std::cout << "✓ Routes configured" << std::endl;
    std::cout << "\nServer running on http://localhost:8080" << std::endl;
    std::cout << "\nAPI Endpoints:" << std::endl;
    std::cout << "  GET  /api/projects   - Get all projects" << std::endl;
    std::cout << "  GET  /api/expertise  - Get all expertise" << std::endl;
    std::cout << "  GET  /api/tools      - Get all tools" << std::endl;
    std::cout << "  POST /api/contact    - Submit contact message" << std::endl;
    std::cout << "  GET  /api/health     - Health check" << std::endl;
    std::cout << "\nPress Ctrl+C to stop...\n" << std::endl;

    app.port(8080).multithreaded().run();

    return 0;
}
