#pragma once

#include <crow_all.hpp>
#include "database.hpp"

namespace portfolio::routes {

class PortfolioRoutes {
public:
    explicit PortfolioRoutes(std::shared_ptr<database::Database> db);
    void setup(crow::SimpleApp& app);

private:
    std::shared_ptr<database::Database> db_;
};

class ApiRoutes {
public:
    explicit ApiRoutes(std::shared_ptr<database::Database> db);
    void setup(crow::SimpleApp& app);

private:
    std::shared_ptr<database::Database> db_;
};

} // namespace portfolio::routes
