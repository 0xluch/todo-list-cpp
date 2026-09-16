#include "folderops.h"
#include "opendb.h"
#include "ui.h"
#include <iostream>
#include <string>
#include <SQLiteCpp/SQLiteCpp.h> 

void createFolder(){
    auto& db = getDB();
    std::cout << "| Enter folder name: ";
    std::cin.ignore();
    std::string fname;
    getline(std::cin, fname); 
    SQLite::Statement query(db, "INSERT INTO folders (folder) VALUES (?);");    
    query.bind(1, fname);
    query.exec();
}

void updateFolderName(){
    auto& db = getDB();
    while(true){
        displayFolder();
        std::cout << "| Choose the folder to update their name: ";
        int idF;
        std::cin >> idF;
        SQLite::Statement folderN(db, "SELECT folder FROM folders WHERE id = ?;");
        folderN.bind(1, idF);
        if(folderN.executeStep()){
            std::string newFName;
            std::cout << "| New folder name: ";
            std::cin.ignore();
            getline(std::cin, newFName);
            std::string orgF = folderN.getColumn(0).getString();
            SQLite::Statement queryt(db, "UPDATE tasks SET folder = ? WHERE folder = ?;");
            queryt.bind(1, newFName);
            queryt.bind(2, orgF);
            queryt.exec();
            SQLite::Statement queryf(db, "UPDATE folders SET folder = ? WHERE id = ?;");
            queryf.bind(1, newFName);
            queryf.bind(2, idF);
            queryf.exec();
            break;
        }else{
            std::cout << "| No folder with that id is found..." << std::endl;
            std::cout << "| Retry(R)/exit(q)" << std::endl;
            char opt;
            std::cin >> opt;
            if(!(opt == 'r' || opt == 'R')) break;
        }
        
    }
}

void deleteFolder(){
    auto& db = getDB();
    while(true){
        displayFolder();
        std::cout << "| Choose the folder to delete (ps: all tasks there will be deleted too): ";
        int idF;
        std::cin >> idF;
        SQLite::Statement folderN(db, "SELECT folder FROM folders WHERE id = ?;");
        folderN.bind(1, idF);
        if(folderN.executeStep()){
            std::string orgF = folderN.getColumn(0).getString();
            SQLite::Statement queryt(db, "DELETE FROM tasks WHERE folder = ?;");
            queryt.bind(1, orgF);
            queryt.exec();
            SQLite::Statement queryf(db, "DELETE FROM folders WHERE id = ?;");
            queryf.bind(1, idF);
            queryf.exec();
            break;
        }else{
            std::cout << "| No folder with that id is found..." << std::endl;
            std::cout << "| Retry(R)/exit(q)" << std::endl;
            std::cout << "| >> ";
            char opt;
            std::cin >> opt;
            if(!(opt == 'r' || opt == 'R')) break;
        }
        
    }
}