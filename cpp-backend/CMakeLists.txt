cmake_minimum_required(VERSION 3.10)
project(PortfolioWebsite VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(Crow REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(sqlite3 REQUIRED)

# Create executable
add_executable(portfolio_server
    src/main.cpp
    src/database/database.cpp
    src/database/models.cpp
    src/routes/portfolio_routes.cpp
    src/routes/api_routes.cpp
    src/middleware/middleware.cpp
)

# Link libraries
target_link_libraries(portfolio_server
    Crow::Crow
    nlohmann_json::nlohmann_json
    sqlite3
)

# Include directories
target_include_directories(portfolio_server PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Compiler flags
if(MSVC)
    target_compile_options(portfolio_server PRIVATE /W4)
else()
    target_compile_options(portfolio_server PRIVATE -Wall -Wextra -pedantic)
endif()
