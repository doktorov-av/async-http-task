//
// Created by DoktorovAlexander on 01.11.2025.
//

#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include <string>
#include <vector>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using Image = std::vector<uint8_t>;

struct Object {
    float x_c;
    float y_c;
    float width;
    float height;
    std::string label;
};

struct Payload {
    double shotLat;
    double shotLon;
    std::vector<Object> objects;
};

struct Message {
    Image image;
    Payload payload;
};

bool IsValid(const Message &message);

void to_json(json &j, const Object &object);
void from_json(const json &j, Object &p);

void to_json(json &j, const Payload &p);

#endif //MESSAGE_HPP
