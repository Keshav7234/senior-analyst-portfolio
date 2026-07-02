#include "../include/middleware.hpp"

namespace portfolio::middleware {

crow::response cors_middleware(const crow::request& req) {
    crow::response res;
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
    return res;
}

void setup_middlewares(crow::SimpleApp& app) {
    // CORS middleware setup can be added here
}

} // namespace portfolio::middleware
