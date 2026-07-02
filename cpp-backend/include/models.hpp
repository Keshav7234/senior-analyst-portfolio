#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace portfolio::models {

struct Project {
    int id;
    std::string title;
    std::string description;
    std::string gradient;
    std::vector<std::string> tags;
    std::string project_type;
    int users_impacted;
    std::string duration;

    json to_json() const {
        return json{
            {"id", id},
            {"title", title},
            {"description", description},
            {"gradient", gradient},
            {"tags", tags},
            {"projectType", project_type},
            {"usersImpacted", users_impacted},
            {"duration", duration}
        };
    }
};

struct Expertise {
    int id;
    std::string title;
    std::string description;
    std::string icon;
    std::string card_color;

    json to_json() const {
        return json{
            {"id", id},
            {"title", title},
            {"description", description},
            {"icon", icon},
            {"cardColor", card_color}
        };
    }
};

struct Tool {
    int id;
    std::string name;
    std::string description;
    std::string icon;
    std::string category;

    json to_json() const {
        return json{
            {"id", id},
            {"name", name},
            {"description", description},
            {"icon", icon},
            {"category", category}
        };
    }
};

struct ContactMessage {
    int id;
    std::string name;
    std::string email;
    std::string subject;
    std::string message;
    std::string sent_at;

    json to_json() const {
        return json{
            {"id", id},
            {"name", name},
            {"email", email},
            {"subject", subject},
            {"message", message},
            {"sentAt", sent_at}
        };
    }
};

} // namespace portfolio::models
