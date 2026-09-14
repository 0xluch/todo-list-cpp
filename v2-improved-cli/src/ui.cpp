#include "ui.h"
#include "storage.h"
#include <vector>
#include <limits>
#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h> 

void displayTask(){
    SQLite::Database db("tasks.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    SQLite::Statement query(db, "SELECT COUNT(*) FROM tasks");
    query.executeStep();
    int count = query.getColumn(0).getInt();
    if (count == 0)
        std::cout << "| You have no tasks registered -_-" << std::endl;
    else{
        SQLite::Statement query(db, "SELECT * FROM tasks");
        while(query.executeStep()){
            int id = query.getColumn(0).getInt();
            std::cout << "| Task " << id << ":" << std::endl;
            std::string title = query.getColumn(1).getString();
            std::string status = query.getColumn(2).getString();
            std::cout << "| Title : " << title
                      << "   ---    " 
                      << "Status: " << status << std::endl;
            std::cout << "─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─" << std::endl;
        }
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
    std::cout << "| choose opr number:" << std::endl;
    std::cout << "|   1. list tasks" << std::endl;
    std::cout << "|   2. add task" << std::endl;
    std::cout << "|   3. update status" << std::endl;
    std::cout << "|   4. update title" << std::endl;
    std::cout << "|   5. delete task" << std::endl;
    std::cout << "|   0. exit" << std::endl;
    std::cout << "|   >> ";
}