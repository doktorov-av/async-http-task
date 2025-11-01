//
// Created by DoktorovAlexander on 01.11.2025.
//

#include "Message.hpp"

bool IsValid(const Message &message) {
    for (const auto &obj: message.payload.objects) {
        if (obj.x_c > 1.f || obj.x_c < 0.f)
            return false;
        if (obj.y_c > 1.f || obj.y_c < 0.f)
            return false;
    }
    return true;
}

void to_json(json &j, const Object &object) {
    j = json{
        {"x_c", object.x_c},
        {"y_c", object.y_c},
        {"width", object.width},
        {"height", object.height},
        {"label", object.label}
    };
}

void from_json(const json &j, Object &p) {
    j.at("x_c").get_to(p.x_c);
    j.at("y_c").get_to(p.y_c);
    j.at("width").get_to(p.width);
    j.at("height").get_to(p.height);
    j.at("label").get_to(p.label);
}

void to_json(json &j, const Payload &p) {
    auto objects = json::array();
    for (const auto &obj: p.objects) {
        objects.emplace_back(obj);
    }

    j = json{
        {"shot_lat", p.shotLat},
        {"shot_lon", p.shotLon},
        {"objects", std::move(objects)}
    };
}
