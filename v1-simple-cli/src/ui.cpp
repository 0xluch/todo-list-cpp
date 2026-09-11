#include "ui.h"
#include "storage.h"
#include <vector>
#include <limits>
#include <iostream>

void displayTask(){
    json listJ = loadTasks();
    auto tasks = listJ.get<std::vector<Task>>();

    if(tasks.empty())
        std::cout << "Empty" << std::endl;
    else{
        for(const auto& t : tasks){
            std::cout << "| id: " << t.id
                 << "\n| title: " << t.title
                 << "\n| status: " << t.status << std::endl;
            std::cout << "\n|─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─\n" << std::endl;
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