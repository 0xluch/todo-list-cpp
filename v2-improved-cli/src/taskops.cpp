#include "taskops.h"
#include "opendb.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <SQLiteCpp/SQLiteCpp.h> 

void addTask(){
    SQLite::Database db("tasktracker.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    db.exec(R"(
        CREATE TABLE IF NOT EXISTS tasks (
            id INTEGER PRIMARY KEY AUTOINCREMENT, 
            title TEXT NOT NULL, 
            status TEXT NOT NULL,
            folder TEXT NOT NULL
            )
        )");
    std::string title;
    std::cout << "| title: ";
    std::cin.ignore();
    getline(std::cin, title);
    std::cout << "| status: ";
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
            std::cout << "Please choose folder: " << std::endl;
            std::cin.ignore();
            getline(std::cin, folder);
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
    SQLite::Database db("tasktracker.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    db.exec(R"(
        CREATE TABLE IF NOT EXISTS tasks (
            id INTEGER PRIMARY KEY AUTOINCREMENT, 
            title TEXT NOT NULL, 
            status TEXT NOT NULL,
            folder TEXT NOT NULL
            )
        )");
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
                std
                std::cout << "| update completed :3" << endl;
            }else{
                std::cout << "| New Title: ";
                std::cin.ignore();
                std::string newTitle;
                std::getline(std::cin, newTitle);
                SQLite::Statement query(db, "UPDATE tasks SET title = ? WHERE id = ?;");
                query.bind(1, newTitle);
                query.bind(2, id);
                query.exec();
                std
                std::cout << "| update completed :3" << endl;
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
    SQLite::Database db("tasktracker.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    db.exec(R"(
        CREATE TABLE IF NOT EXISTS tasks (
            id INTEGER PRIMARY KEY AUTOINCREMENT, 
            title TEXT NOT NULL, 
            status TEXT NOT NULL,
            folder TEXT NOT NULL
            )
        )");

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