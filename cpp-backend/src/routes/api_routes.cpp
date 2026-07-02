#include <crow_all.hpp>
#include "../include/routes.hpp"
#include "../include/middleware.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace portfolio::routes {

PortfolioRoutes::PortfolioRoutes(std::shared_ptr<database::Database> db)
    : db_(db) {}

void PortfolioRoutes::setup(crow::SimpleApp& app) {
    // Home page
    CROW_ROUTE(app, "/")
    ([this]() {
        auto response = crow::response{
            "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Senior Infrastructure Analyst | Enterprise Systems Expert</title><link rel='stylesheet' href='styles.css'><link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.0/css/all.min.css'><link href='https://fonts.googleapis.com/css2?family=Poppins:wght@300;400;600;700;800&family=Playfair+Display:wght@700&display=swap' rel='stylesheet'></head><body><nav class='navbar'><div class='container'><div class='nav-wrapper'><div class='logo'><span class='logo-icon'>🔐</span><h1>Senior Analyst</h1></div><ul class='nav-menu'><li><a href='#home' class='nav-link active'>Home</a></li><li><a href='#about' class='nav-link'>About</a></li><li><a href='#expertise' class='nav-link'>Expertise</a></li><li><a href='#projects' class='nav-link'>Projects</a></li><li><a href='#contact' class='nav-link'>Contact</a></li></ul></div></div></nav><section id='home' class='hero'><div class='hero-content'><div class='hero-text'><h1 class='hero-title'>Enterprise Infrastructure <span class='gradient-text'>Excellence</span></h1><p class='hero-subtitle'>Mastering Active Directory, Citrix, Exchange, Entra ID & Enterprise Solutions</p><div class='cta-buttons'><button class='btn btn-primary' onclick='document.getElementById(\"projects\").scrollIntoView({behavior: \"smooth\"})'>View Projects</button><button class='btn btn-secondary' onclick='document.getElementById(\"contact\").scrollIntoView({behavior: \"smooth\"})'>Get In Touch</button></div></div></div></section><footer><p>&copy; 2026 Senior Infrastructure Analyst | Powered by C++ Crow Framework</p></footer><script src='script.js'></script></body></html>"
        };
        response.set_header("Content-Type", "text/html; charset=utf-8");
        return response;
    });
}

ApiRoutes::ApiRoutes(std::shared_ptr<database::Database> db)
    : db_(db) {}

void ApiRoutes::setup(crow::SimpleApp& app) {
    // Get all projects
    CROW_ROUTE(app, "/api/projects")
    ([this]() {
        auto projects = db_->get_all_projects();
        json response = json::array();
        for (const auto& p : projects) {
            response.push_back(p.to_json());
        }
        auto res = crow::response{response.dump()};
        res.set_header("Content-Type", "application/json");
        return res;
    });

    // Get all expertise
    CROW_ROUTE(app, "/api/expertise")
    ([this]() {
        auto expertise = db_->get_all_expertise();
        json response = json::array();
        for (const auto& e : expertise) {
            response.push_back(e.to_json());
        }
        auto res = crow::response{response.dump()};
        res.set_header("Content-Type", "application/json");
        return res;
    });

    // Get all tools
    CROW_ROUTE(app, "/api/tools")
    ([this]() {
        auto tools = db_->get_all_tools();
        json response = json::array();
        for (const auto& t : tools) {
            response.push_back(t.to_json());
        }
        auto res = crow::response{response.dump()};
        res.set_header("Content-Type", "application/json");
        return res;
    });

    // Submit contact message
    CROW_ROUTE(app, "/api/contact")
        .methods("POST"_method)
    ([this](const crow::request& req) {
        try {
            auto data = json::parse(req.body);
            portfolio::models::ContactMessage msg;
            msg.name = data["name"];
            msg.email = data["email"];
            msg.subject = data["subject"];
            msg.message = data["message"];

            bool success = db_->add_message(msg);
            json response = {{
                {"success", success},
                {"message", success ? "Message sent successfully" : "Failed to send message"}
            }};

            auto res = crow::response{response.dump()};
            res.set_header("Content-Type", "application/json");
            return res;
        } catch (const std::exception& e) {
            json error = {{"success", false}, {"error", e.what()}};
            auto res = crow::response(400, error.dump());
            res.set_header("Content-Type", "application/json");
            return res;
        }
    });

    // Health check
    CROW_ROUTE(app, "/api/health")
    ([]() {
        json health = {{
            {"status", "healthy"},
            {"timestamp", "2026-07-02"},
            {"service", "Senior Analyst Portfolio"}
        }};
        auto res = crow::response{health.dump()};
        res.set_header("Content-Type", "application/json");
        return res;
    });
}

} // namespace portfolio::routes
