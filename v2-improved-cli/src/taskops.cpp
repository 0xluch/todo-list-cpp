#include "taskops.h"
#include "opendb.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <SQLiteCpp/SQLiteCpp.h> 

void addTask(){
    auto& db = getDB();
    std::string title;
    std::cout << "| title: ";
    std::cin.ignore();
    getline(std::cin, title);
    std::cout << "| status: " << std::endl;;
    std::string thisStatus = status();
    std::string folder;
    while(true){
        std::cout << "| Wanna choose a specific folder? (Y/N) ";
        char f;
        std::cin >> f;
        if (f == 'N'){
            folder = "default";
            break;
        }else if (f == 'Y'){
            displayFolder();
            std::cout << "| Please choose folder: ";
            int idF;
            std::cin >> idF;
            SQLite::Statement queryf(db, "SELECT * FROM folders WHERE id = ?;");
            queryf.bind(1, idF);
            if (queryf.executeStep()){
                folder = queryf.getColumn(1).getString();
                break;
            }else
                std::cout << "| Folder not found." << std::endl;
        }else
            std::cout << "| Invalid option, try again." << std::endl;
        
    }
    SQLite::Statement query(db, "INSERT INTO tasks (title, status, folder) VALUES (?, ?, ?)");
    
    query.bind(1, title);
    query.bind(2, thisStatus);
    query.bind(3, folder);
    query.exec();
}

void update(int& id, char opr){
    auto& db = getDB();
    SQLite::Statement query(db, "SELECT id FROM tasks;");
    bool found = false;
    while (query.executeStep()){
        if(query.getColumn(0).getInt() == id){
            found = true;
            if (opr == 's'){
                std::cout << "| New status: " << std::endl;
                std::string newStatus = status();
                SQLite::Statement query(db, "UPDATE tasks SET status = ? WHERE id = ?;");
                query.bind(1, newStatus);
                query.bind(2, id);
                query.exec();
                std::cout << "| ─ ─ ─ ─ ─ ─ ─ ─ ─ ─" << std::endl;
                std::cout << "| update completed :3" << std::endl;
                std::cout << "| ─ ─ ─ ─ ─ ─ ─ ─ ─ ─" << std::endl;
            }else{
                std::cout << "| New Title: ";
                std::cin.ignore();
                std::string newTitle;
                std::getline(std::cin, newTitle);
                SQLite::Statement query(db, "UPDATE tasks SET title = ? WHERE id = ?;");
                query.bind(1, newTitle);
                query.bind(2, id);
                query.exec();
                std::cout << "| ─ ─ ─ ─ ─ ─ ─ ─ ─ ─" << std::endl;
                std::cout << "| update completed :3" << std::endl;
                std::cout << "| ─ ─ ─ ─ ─ ─ ─ ─ ─ ─" << std::endl;
            }
            break;
        }
    }
    if(!found){
        std::cout << "id not found, check tasks list" << std::endl;
        displayTask();
    }
}

void updateTitle(int& id){
    update(id, 't');
}

void updateStatus(int& id){
    update(id, 's');
}

void deleteTask(int& id){
    auto& db = getDB();
    SQLite::Statement query(db, "SELECT id FROM tasks;");
    bool found = false;
    while (query.executeStep()){
        if(query.getColumn(0).getInt() == id){
            found = true;
            std::cout << "| task found... " << std::endl;;
            SQLite::Statement query(db, "DELETE FROM tasks WHERE id = ?;");
            query.bind(1, id);
            query.exec();
            std::cout << "| task deleted :3" << std::endl;
            break;
        }
    }
    if(!found)
        std::cout << "id not found, check list" << std::endl;
}