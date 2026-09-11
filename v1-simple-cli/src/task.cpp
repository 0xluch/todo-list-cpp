#include "task.h"

void to_json(json& j, const Task task){
    j = nlohmann::json{{"id", task.id}, {"title", task.title}, {"status", task.status}};
}

void from_json(const json& j, Task& task){
    j.at("id").get_to(task.id);
    j.at("title").get_to(task.title);
    j.at("status").get_to(task.status);
}