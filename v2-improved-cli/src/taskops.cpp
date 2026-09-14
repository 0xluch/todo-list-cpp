#include "taskops.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <SQLiteCpp/SQLiteCpp.h> 

void addTask(){
    SQLite::Database db("tasks.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    db.exec(R"(
        CREATE TABLE IF NOT EXISTS tasks (
            id INTEGER PRIMARY KEY AUTOINCREMENT, 
            title TEXT NOT NULL, 
            status TEXT NOT NULL
            )
        )"
        );
    std::string title, status;
    std::cout << "| title: ";
    std::cin.ignore();
    getline(std::cin, title);
    std::cout << "| status: ";
    getline(std::cin, status);
    SQLite::Statement query(db, "INSERT INTO tasks (title, status) VALUES (?, ?)");
    query.bind(1, title);
    query.bind(2, status);
    query.exec();
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