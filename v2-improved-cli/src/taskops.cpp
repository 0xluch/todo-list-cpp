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
    std::cout << "| status: " << std::endl;
    std::string thisStatus = status();
    int folderID;
    while(true){
        std::cout << "| Wanna choose a specific folder? (Y/N) ";
        char f;
        std::cin >> f;
        if (f == 'N'){
            folderID = 1;
            break;
        }else if (f == 'Y'){
            displayFolder();
            std::cout << "| Please choose folder: ";
            int idF;
            std::cin >> idF;
            SQLite::Statement queryf(db, "SELECT id FROM folders WHERE id = ?;");
            queryf.bind(1, idF);
            if (queryf.executeStep()){
                folderID = idF;
                break;
            }else
                std::cout << "| Folder not found." << std::endl;
        }else
            std::cout << "| Invalid option, try again." << std::endl;
        
    }
    SQLite::Statement query(db, "INSERT INTO tasks (title, status, folder_id) VALUES (?, ?, ?)");
    
    query.bind(1, title);
    query.bind(2, thisStatus);
    query.bind(3, folderID);
    query.exec();
}

void updateTitle(int id){
    auto& db = getDB();
    while(true){
        SQLite::Statement selectQuery(db, "SELECT id FROM tasks WHERE id = ?;");
        selectQuery.bind(1, id);
        if (selectQuery.executeStep()){
            std::cout << "| New Title: ";
            std::cin.ignore();
            std::string newTitle;
            std::getline(std::cin, newTitle);
            SQLite::Statement updateQuery(db, "UPDATE tasks SET title = ? WHERE id = ?;");
            updateQuery.bind(1, newTitle);
            updateQuery.bind(2, id);
            updateQuery.exec();
            std::cout << "| ─ ─ ─ ─ ─ ─ ─ ─ ─ ─" << std::endl;
            std::cout << "| update completed :3" << std::endl;  
            std::cout << "| ─ ─ ─ ─ ─ ─ ─ ─ ─ ─" << std::endl;
            break;
        }else {
            std::cout << "id not found, check tasks list" << std::endl;
            std::cout << "| Retry(R)/exit(q)" << std::endl;
            char opt;
            std::cin >> opt;
            if(!(opt == 'r' || opt == 'R')) break;
            displayTask();
        }
    }
}

void updateStatus(int id){
    auto& db = getDB();
    while(true){
        SQLite::Statement selectQuery(db, "SELECT id FROM tasks WHERE id = ?;");
        selectQuery.bind(1, id);
        if (selectQuery.executeStep()){
            std::cout << "| New status: " << std::endl;
            std::string newStatus = status();
            SQLite::Statement updateQuery(db, "UPDATE tasks SET status = ? WHERE id = ?;");
            updateQuery.bind(1, newStatus);
            updateQuery.bind(2, id);
            updateQuery.exec();
            std::cout << "| ─ ─ ─ ─ ─ ─ ─ ─ ─ ─" << std::endl;
            std::cout << "| update completed :3" << std::endl;
            std::cout << "| ─ ─ ─ ─ ─ ─ ─ ─ ─ ─" << std::endl;
            break;
        }else {
            std::cout << "id not found, check tasks list" << std::endl;
            std::cout << "| Retry(R)/exit(q)" << std::endl;
            char opt;
            std::cin >> opt;
            if(!(opt == 'r' || opt == 'R')) break;
            displayTask();
        }
    }
}

void deleteTask(int id){
    auto& db = getDB();
    while(true){
        SQLite::Statement query(db, "SELECT id FROM tasks WHERE id = ?;");
        query.bind(1, id);
        if(query.executeStep()){
            std::cout << "| task found... " << std::endl;
            SQLite::Statement deleteQuery(db, "DELETE FROM tasks WHERE id = ?;");
            deleteQuery.bind(1, id);
            deleteQuery.exec();
            std::cout << "| task deleted :3" << std::endl;
            break;
        }else{
            std::cout << "id not found, check list" << std::endl;
            std::cout << "| Retry(R)/exit(q)" << std::endl;
            char opt;
            std::cin >> opt;
            if(!(opt == 'r' || opt == 'R')) break;
            displayTask();
        }
    }
}