# Senior Analyst Portfolio - C++ Backend

Modern C++ web application using Crow framework with SQLite database.

## Build Instructions

### Prerequisites
- C++20 compatible compiler (GCC 10+, Clang 10+, MSVC 2019+)
- CMake 3.10+
- vcpkg (for dependency management)

### Installation

```bash
# Install dependencies with vcpkg
vcpkg install crow nlohmann-json sqlite3

# Create build directory
mkdir build && cd build

# Generate build files
cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg path]/scripts/buildsystems/vcpkg.cmake

# Build
cmake --build . --config Release

# Run
./portfolio_server
```

Server starts on `http://localhost:8080`

## API Endpoints

- `GET /` - Home page
- `GET /api/projects` - Get all projects (JSON)
- `GET /api/expertise` - Get all expertise (JSON)
- `GET /api/tools` - Get all tools (JSON)
- `POST /api/contact` - Submit contact message
- `GET /api/health` - Health check

## Architecture

- **Framework**: Crow (C++ web framework)
- **Database**: SQLite3 with C++ bindings
- **JSON**: nlohmann/json
- **Pattern**: RESTful API + Server-side rendering
