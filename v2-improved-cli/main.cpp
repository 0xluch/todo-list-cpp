#include"src/task.h"
#include "src/storage.h"
#include "src/taskops.h"
#include "src/ui.h"
#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h> 



int main(){
    std::cout << "                                                  " << R"(    |\__/,|   (`\ )" << "\n" 
    << "                                                    _.|o o  |_   ) )" << std::endl;
    std::cout << "+-Welcome to your to-do list!─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─(((─ ─(((─ ─ ─ ─ ─ ─ ─+\n|" << std::endl;
    showMenu();
    int opr;
    while(std::cin >> opr){
        if(opr == 1){
            std::cout << std::endl;
            displayTask();
        }else if(opr == 2){
            try {
                addTask();
            } catch (const SQLite::Exception& e) {
                std::cerr << e.what() << std::endl;
            }
        }else if(opr == 3){
            int id;
            std::cout << "| task id to be updated: ";
            std::cin >> id;
            updateStatus(id);
        }else if(opr == 4){
            int id;
            std::cout << "| task id to be updated: ";
           std::cin >> id;
            updateTitle(id);
        }else if(opr == 5){
            int id;
            std::cout << "| task id to be deleted: ";
            std::cin >> id;
            deleteTask(id);
        }else if(opr == 9){
            
        }else
            break;
        showMenu();
    }
}
