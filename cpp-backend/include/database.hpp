#pragma once

#include <string>
#include <vector>
#include <memory>
#include "models.hpp"

namespace portfolio::database {

class Database {
public:
    Database(const std::string& db_path);
    ~Database();

    // Initialize database
    bool init();

    // Project operations
    std::vector<models::Project> get_all_projects();
    models::Project get_project(int id);
    bool add_project(const models::Project& project);
    bool update_project(const models::Project& project);
    bool delete_project(int id);

    // Expertise operations
    std::vector<models::Expertise> get_all_expertise();
    models::Expertise get_expertise(int id);
    bool add_expertise(const models::Expertise& expertise);

    // Tool operations
    std::vector<models::Tool> get_all_tools();
    models::Tool get_tool(int id);
    bool add_tool(const models::Tool& tool);

    // Contact messages
    std::vector<models::ContactMessage> get_all_messages();
    bool add_message(const models::ContactMessage& message);

private:
    std::string db_path_;
    void* db_handle_; // sqlite3* stored as void*

    void create_tables();
    void seed_data();
};

} // namespace portfolio::database
