#include "taskops.h"
#include "opendb.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

void addTask(){
    openDB();
    std::string title, status;
    std::cout << "| title: ";
    std::cin.ignore();
    getline(std::cin, title);
    std::cout << "| status: ";
    getline(std::cin, status);
    while(true){
        std::cout << "| Wanna choose a specific folder? (Y/N) ";
        char f;
        std::cin >> f;
        std::string folder;
        if (f == 'N'){
            folder = "default";
            break;
        }else if (f == 'Y'){
            displayFolder();
            std::cout << "Please choose folder: " << std::endl;
            cin.ignore();
            getline(cin, folder);
        }else
            std::cout << "| Invalid option, try again." << std::endl;
    }
    SQLite::Statement query(db, "INSERT INTO tasks (title, status, folder) VALUES (?, ?, ?)");
    query.bind(1, title);
    query.bind(2, status);
    query.bind(3, folder);
    query.exec();
}

void update(int& id, char opr){
    openDB();
    SQLite::Statement query(db, "SELECT id FROM tasks;");
    bool found = false;
    while (query.executeStep()){
        if(query.getColumn(0).getInt() == id){
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