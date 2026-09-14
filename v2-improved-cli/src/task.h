#pragma once
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

struct Task {
    int id;
    std::string title, status;
};

void to_json(json& j, const Task task);
void from_json(const json& j, Task& task);