#include "ui.h"
#include "opendb.h"
#include <vector>
#include <limits>
#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h> 


void displayTask(){
    auto& db = getDB();
    SQLite::Statement query(db, "SELECT COUNT(*) FROM tasks");
    query.executeStep();
    int count = query.getColumn(0).getInt();
    if (count == 0)
        std::cout << "| You have no tasks registered -_-" << std::endl;
    else{
        SQLite::Statement queryf(db, "SELECT DISTINCT folder FROM tasks");
        while(queryf.executeStep()){
            std::string folder = queryf.getColumn(0).getString();
            std::vector<std::string> folders;
            folders.push_back(folder); 
            std::cout << "| #" << folder << ": " << std::endl;
            SQLite::Statement query(db, "SELECT * FROM tasks WHERE folder = ?;");
            query.bind(1, folder);
            while(query.executeStep()){
                int id = query.getColumn(0).getInt();
                std::cout << "| Task id = " << id << ":" << std::endl;
                std::string title = query.getColumn(1).getString();
                std::string status = query.getColumn(2).getString();
                std::cout << "|  Title : " << title
                          << "   ---    " 
                          << "Status: " << status << std::endl;
                std::cout << "|" << std::endl;
            }
            std::cout << "|─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─" << std::endl;
        }
    }
}

void displayFolder(){
    try{
        auto& db = getDB();
        SQLite::Statement query(db, "SELECT * FROM folders;");
        int i = 0;
        while(query.executeStep()){
            i++;
            std::string folder = query.getColumn(1).getText();
            std::cout << "| Folder id = " << query.getColumn(0).getInt() << ": " << folder << std::endl;
        }
        if (i == 0)
            std::cout << "You have no folder yet" << std::endl;
    }catch (const SQLite::Exception& e){
        std::cerr << e.what() << std::endl; 
    }
}

std::string status(){
    int opt;

    while (true) {
        std::cout << "| 1. Completed" << std::endl;
        std::cout << "| 2. In-progress" << std::endl;
        std::cout << "| 3. Pending" << std::endl;
        std::cout << "| >> ";

        std::cin >> opt;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "| Invalid option, try again." << std::endl;
            continue;
        }

        if (opt == 1) return "Completed";
        if (opt == 2) return "In-progress";
        if (opt == 3) return "Pending";

        std::cout << "| Invalid option, try again." << std::endl;
    }
}

void showMenu(){
    std::cout << "|─choose opr number:" << std::endl;
    std::cout << "|─display options:─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─" << std::endl;
    std::cout << "|   1. list all tasks" << std::endl;
    std::cout << "|   2. list folders" << std::endl;
    std::cout << "|─tasks ops:─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─" << std::endl;
    std::cout << "|   3. add task" << std::endl;
    std::cout << "|   4. update task status" << std::endl;
    std::cout << "|   5. update task title" << std::endl;
    std::cout << "|   6. delete task" << std::endl;
    std::cout << "|─folders ops:─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─" << std::endl;
    std::cout << "|   7. create folder" << std::endl;
    std::cout << "|   8. update folder name" << std::endl;
    std::cout << "|   9. delete folder" << std::endl;
    std::cout << "|─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─" << std::endl;
    std::cout << "|   0. exit" << std::endl;
    std::cout << "|   >> ";
}