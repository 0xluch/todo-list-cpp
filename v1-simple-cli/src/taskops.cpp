#include "taskops.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

void addTask(){
    Task t;
    std::cout << "| title: ";
    std::cin.ignore();
    std::getline(std::cin, t.title);
    std::cout << "| Choose status: " << std::endl;
    t.status = status();
    json listJ = loadTasks();

    int size = 1;
    if(!listJ.empty()){
        int maxId = 0;
        for(const auto& element : listJ){
            if(element.contains("id"))
                maxId = std::max(maxId, element["id"].get<int>());
        }
        size += maxId;
    }
    t.id = size;
    json j;
    to_json(j, t);
    listJ.push_back(j);
    saveTasks(listJ);
}

void update(int& id, char opr){
    json j = loadTasks();
    bool found = false;
    for (auto& target : j){
        if(target.contains("id") && target["id"].get<int>() == id){
            found = true;
            if (opr == 's'){
                std::cout << "| New status: " << std::endl;
                std::string newStatus = status();
                target["status"] = newStatus;
            }else{
                std::cout << "| New Title: ";
                std::cin.ignore();
                std::string newTitle;
                std::getline(std::cin, newTitle);
                target["title"] = newTitle;
            }
            saveTasks(j);
            break;
        }
    }
    if(!found)
        std::cout << "id not found, check list" << std::endl;
}

void updateTitle(int& id){
    update(id, 't');
}

void updateStatus(int& id){
    update(id, 's');
}

void deleteTask(int& id){
    json j = loadTasks();
    bool found = false;
    for (auto it = j.begin(); it != j.end(); ){
        if(it->contains("id") && (*it)["id"].get<int>() == id){
            found = true;
            std::cout << "| task found... ";
            it = j.erase(it);
            saveTasks(j);
            break;
        }else
            ++it;
    }
    if(!found)
        std::cout << "id not found, check list" << std::endl;
}