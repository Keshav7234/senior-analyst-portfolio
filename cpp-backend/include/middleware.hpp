#pragma once

#include <crow_all.hpp>
#include <string>

namespace portfolio::middleware {

crow::response cors_middleware(const crow::request& req);
void setup_middlewares(crow::SimpleApp& app);

} // namespace portfolio::middleware
