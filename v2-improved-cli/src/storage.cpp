#include "storage.h"
#include <fstream>
#include <iostream>

void saveTasks(const json& listJ){
    std::ofstream outFile("TaskList.json");
    if(outFile.is_open()){
        outFile << listJ.dump(4);
        outFile.close();
        std::cout << "| Done :3" << std::endl;
    }else
        std::cout << "Error opening file (either corrupted or not found)" << std::endl;
}

json loadTasks(){
    json listJ = json::array();
    std::ifstream file("TaskList.json");
    if (file.is_open()){
        if(file.peek() == std::ifstream::traits_type::eof())
            std::cout << "| Empty file" << std::endl;
        else
            file >> listJ;
        file.close();
    }
    return listJ;
}