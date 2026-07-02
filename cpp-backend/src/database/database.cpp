#include <sqlite3.h>
#include <iostream>
#include <sstream>
#include <chrono>
#include "../include/database.hpp"

namespace portfolio::database {

Database::Database(const std::string& db_path)
    : db_path_(db_path), db_handle_(nullptr) {}

Database::~Database() {
    if (db_handle_) {
        sqlite3_close(static_cast<sqlite3*>(db_handle_));
    }
}

bool Database::init() {
    sqlite3* db = nullptr;
    int rc = sqlite3_open(db_path_.c_str(), &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    db_handle_ = db;
    create_tables();
    seed_data();
    return true;
}

void Database::create_tables() {
    sqlite3* db = static_cast<sqlite3*>(db_handle_);
    char* err_msg = nullptr;

    const char* sql_projects = R"(
        CREATE TABLE IF NOT EXISTS projects (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL,
            description TEXT,
            gradient TEXT,
            project_type TEXT,
            users_impacted INTEGER,
            duration TEXT,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP
        );
    )";

    const char* sql_expertise = R"(
        CREATE TABLE IF NOT EXISTS expertise (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL,
            description TEXT,
            icon TEXT,
            card_color TEXT,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP
        );
    )";

    const char* sql_tools = R"(
        CREATE TABLE IF NOT EXISTS tools (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            description TEXT,
            icon TEXT,
            category TEXT,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP
        );
    )";

    const char* sql_messages = R"(
        CREATE TABLE IF NOT EXISTS contact_messages (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            email TEXT NOT NULL,
            subject TEXT NOT NULL,
            message TEXT NOT NULL,
            sent_at DATETIME DEFAULT CURRENT_TIMESTAMP
        );
    )";

    const char* sql_project_tags = R"(
        CREATE TABLE IF NOT EXISTS project_tags (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            project_id INTEGER NOT NULL,
            tag TEXT NOT NULL,
            FOREIGN KEY(project_id) REFERENCES projects(id) ON DELETE CASCADE
        );
    )";

    std::vector<const char*> sql_statements = {
        sql_projects, sql_expertise, sql_tools, sql_messages, sql_project_tags
    };

    for (const auto& sql : sql_statements) {
        if (sqlite3_exec(db, sql, nullptr, nullptr, &err_msg) != SQLITE_OK) {
            std::cerr << "SQL error: " << err_msg << std::endl;
            sqlite3_free(err_msg);
        }
    }
}

void Database::seed_data() {
    sqlite3* db = static_cast<sqlite3*>(db_handle_);
    char* err_msg = nullptr;

    // Check if data already exists
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM projects", -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int count = sqlite3_column_int(stmt, 0);
            sqlite3_finalize(stmt);
            if (count > 0) return; // Data already exists
        }
    }

    const char* insert_projects = R"(
        INSERT INTO projects (title, description, gradient, project_type, users_impacted, duration)
        VALUES 
            ('AD Forest Consolidation', 'Successfully migrated 50,000+ users across 3 domains into unified forest with zero downtime.', 'gradient-1', 'Active Directory', 50000, '6 months'),
            ('Citrix XenDesktop Deployment', 'Architected and deployed VDI environment supporting 10,000 concurrent users with 99.99% uptime SLA', 'gradient-2', 'Citrix', 10000, '8 months'),
            ('Exchange 2016 to 2019 Migration', 'Planned and executed enterprise-wide Exchange migration for 30,000 mailboxes with zero data loss', 'gradient-3', 'Exchange', 30000, '4 months'),
            ('Hybrid Identity Solution', 'Implemented Entra ID Connect with MFA, conditional access policies, and seamless cloud integration', 'gradient-4', 'Entra ID', 25000, '3 months'),
            ('BeyondTrust PAM Implementation', 'Deployed privileged access management system with session recording and compliance audit trails', 'gradient-5', 'Security', 5000, '5 months'),
            ('Disaster Recovery Setup', 'Built comprehensive DR solution for critical infrastructure with automated failover and RPO < 1 hour', 'gradient-6', 'Infrastructure', 100000, '7 months');
    )";

    const char* insert_expertise = R"(
        INSERT INTO expertise (title, description, icon, card_color)
        VALUES
            ('Active Directory', 'Domain architecture, GPO management, user provisioning, security hardening, and hybrid cloud integration', 'fas fa-key', 'card-blue'),
            ('Citrix & VDI', 'Virtual desktop infrastructure, Citrix XenDesktop, workspace management, and performance optimization', 'fas fa-window-restore', 'card-purple'),
            ('Exchange Server', 'Email administration, mailbox management, disaster recovery, migration planning, and hybrid deployment', 'fas fa-envelope', 'card-teal'),
            ('Entra ID & Azure', 'Cloud identity management, conditional access, hybrid sync, and Azure resource administration', 'fas fa-cloud', 'card-coral'),
            ('Remote Access', 'Bomgar/BeyondTrust implementation, VPN solutions, and secure remote support infrastructure', 'fas fa-tools', 'card-green'),
            ('Systems Architecture', 'Infrastructure design, capacity planning, redundancy, and business continuity solutions', 'fas fa-network-wired', 'card-orange');
    )";

    const char* insert_tools = R"(
        INSERT INTO tools (name, description, icon, category)
        VALUES
            ('Windows Server', '2012 R2, 2016, 2019, 2022', 'fas fa-server', 'Infrastructure'),
            ('Active Directory', 'Domain Services, Certificate Services', 'fas fa-lock', 'Identity'),
            ('Citrix', 'XenDesktop, XenApp, NetScaler', 'fas fa-desktop', 'Virtualization'),
            ('Exchange', '2013, 2016, 2019, Online', 'fas fa-envelope', 'Messaging'),
            ('Azure & Entra ID', 'Azure AD, Conditional Access', 'fas fa-cloud', 'Cloud'),
            ('BeyondTrust', 'PAM, Session Recording', 'fas fa-shield-alt', 'Security'),
            ('Splunk', 'Log analysis and monitoring', 'fas fa-chart-line', 'Monitoring'),
            ('PowerShell', 'Automation and scripting', 'fas fa-code-branch', 'Automation'),
            ('Veeam', 'Backup and disaster recovery', 'fas fa-database', 'Backup'),
            ('VMware', 'Virtualization platform', 'fas fa-globe', 'Virtualization'),
            ('Networking', 'VPN, Firewall, DNS, DHCP', 'fas fa-network-wired', 'Infrastructure'),
            ('Compliance', 'GDPR, HIPAA, ISO 27001', 'fas fa-check-circle', 'Compliance');
    )";

    std::vector<const char*> insert_statements = {
        insert_projects, insert_expertise, insert_tools
    };

    for (const auto& sql : insert_statements) {
        if (sqlite3_exec(db, sql, nullptr, nullptr, &err_msg) != SQLITE_OK) {
            std::cerr << "SQL error: " << err_msg << std::endl;
            sqlite3_free(err_msg);
        }
    }
}

std::vector<models::Project> Database::get_all_projects() {
    std::vector<models::Project> projects;
    sqlite3* db = static_cast<sqlite3*>(db_handle_);
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, "SELECT id, title, description, gradient, project_type, users_impacted, duration FROM projects", -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement" << std::endl;
        return projects;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        models::Project p;
        p.id = sqlite3_column_int(stmt, 0);
        p.title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        p.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        p.gradient = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        p.project_type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        p.users_impacted = sqlite3_column_int(stmt, 5);
        p.duration = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));

        // Get tags for this project
        sqlite3_stmt* tag_stmt = nullptr;
        if (sqlite3_prepare_v2(db, "SELECT tag FROM project_tags WHERE project_id = ?", -1, &tag_stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_int(tag_stmt, 1, p.id);
            while (sqlite3_step(tag_stmt) == SQLITE_ROW) {
                p.tags.push_back(reinterpret_cast<const char*>(sqlite3_column_text(tag_stmt, 0)));
            }
            sqlite3_finalize(tag_stmt);
        }

        projects.push_back(p);
    }

    sqlite3_finalize(stmt);
    return projects;
}

std::vector<models::Expertise> Database::get_all_expertise() {
    std::vector<models::Expertise> expertise_list;
    sqlite3* db = static_cast<sqlite3*>(db_handle_);
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, "SELECT id, title, description, icon, card_color FROM expertise", -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement" << std::endl;
        return expertise_list;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        models::Expertise e;
        e.id = sqlite3_column_int(stmt, 0);
        e.title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        e.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        e.icon = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        e.card_color = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        expertise_list.push_back(e);
    }

    sqlite3_finalize(stmt);
    return expertise_list;
}

std::vector<models::Tool> Database::get_all_tools() {
    std::vector<models::Tool> tools;
    sqlite3* db = static_cast<sqlite3*>(db_handle_);
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, "SELECT id, name, description, icon, category FROM tools", -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement" << std::endl;
        return tools;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        models::Tool t;
        t.id = sqlite3_column_int(stmt, 0);
        t.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        t.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        t.icon = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        t.category = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        tools.push_back(t);
    }

    sqlite3_finalize(stmt);
    return tools;
}

bool Database::add_message(const models::ContactMessage& message) {
    sqlite3* db = static_cast<sqlite3*>(db_handle_);
    sqlite3_stmt* stmt = nullptr;

    const char* sql = "INSERT INTO contact_messages (name, email, subject, message) VALUES (?, ?, ?, ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement" << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, message.name.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, message.email.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, message.subject.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, message.message.c_str(), -1, SQLITE_STATIC);

    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return success;
}

std::vector<models::ContactMessage> Database::get_all_messages() {
    std::vector<models::ContactMessage> messages;
    sqlite3* db = static_cast<sqlite3*>(db_handle_);
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, "SELECT id, name, email, subject, message, sent_at FROM contact_messages ORDER BY sent_at DESC", -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement" << std::endl;
        return messages;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        models::ContactMessage m;
        m.id = sqlite3_column_int(stmt, 0);
        m.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        m.email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        m.subject = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        m.message = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        m.sent_at = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        messages.push_back(m);
    }

    sqlite3_finalize(stmt);
    return messages;
}

} // namespace portfolio::database
