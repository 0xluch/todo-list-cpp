#include<iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>

using namespace std;
using json = nlohmann::json;

struct Task {
    int id;
    string title, status;
};

void to_json(json& j, const Task task){
    j = json{{"id", task.id}, {"title", task.title}, {"status", task.status}};
}

void from_json(const json& j, Task& task){
    j.at("id").get_to(task.id);
    j.at("title").get_to(task.title);
    j.at("status").get_to(task.status);
}

void addTask(Task t){
    cout << "id: ";
    cin >> t.id;
    cout << "title: ";
    cin >> t.title;
    cout << "status: ";
    cin >> t.status;
    json j;
    to_json (j, t);
    //////////////////////
    json listJ = json::array();
    ifstream file("TaskList.json");
    if(file.is_open()){
        file >> listJ;
        cout << "loading" << endl;
    }else
        cout << "error...1" << endl;

    listJ.push_back(j);
    ofstream outFile("TaskList.json");
    if(outFile.is_open()){
        outFile << listJ.dump(4);
        outFile.close();
        cout << "Done :3" << endl;
    }else
        cout << "error...2" << endl;
}


int main(){
    cout << "Welcome to you r to-do list!" << endl;
    cout << "choose opr:" << endl;
    cout << "1. add" << endl;
    int opr;
    while(cin >> opr){
        if(opr == 1){
            Task t;
            addTask(t);
        }
        cout << "choose opr:" << endl;
        cout << "1. add" << endl;
    }
}
