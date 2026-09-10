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

void displayTask(){
    json listJ = json::array();
    ifstream file("TaskList.json");
    if (file.is_open()){
        if(file.peek() == ifstream::traits_type::eof())
            cout << "| Empty file" << endl;
        else{
        file >> listJ;
        file.close();
        auto tasks = listJ.get<vector<Task>>();
        if(tasks.empty())
            cout << "Empty" << endl;
        else{
            for(const auto& t : tasks){
                cout << "| id: " << t.id
                     << "\n| title: " << t.title
                     << "\n| status: " << t.status << endl;
                cout << "\n|─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─\n" << endl;
            }
        }
    }
    }else
        cout << "display error" << endl;
}

void addTask(Task t){
    cout << "| title: ";
    cin.ignore();
    getline(cin, t.title);
    cout << "| status: ";
    cin >> t.status;
    json listJ = json::array();
    ifstream file("TaskList.json");
    if(file.is_open()){
        if(file.peek() != ifstream::traits_type::eof()){
            file >> listJ;
        }
        file.close();
    }else
        cout << "error...1" << endl;
    int size = 1;
    if(!listJ.empty()){
        int maxId;
        for(const auto& element : listJ){
            if(element.contains("id"))
                maxId = max(maxId, element["id"].get<int>());
        }
        size++;
    }
    json j;
    to_json (j, t);
    listJ.push_back(j);
    ofstream outFile("TaskList.json");
    if(outFile.is_open()){
        outFile << listJ.dump(4);
        outFile.close();
        cout << "| Done :3" << endl;
    }else
        cout << "error...2" << endl;
}

void updateTask(int& id){
    ifstream file("TaskList.json");
    json j = json::array();
    bool isEmpty = true;
    if(file.is_open()){
        if(file.peek() != ifstream::traits_type::eof()){
            file >> j;
            isEmpty = false;
        }
        file.close();
    }
    if (!isEmpty){
    bool found = false;
    for (auto& target : j){
        if(target.contains("id") && target["id"].get<int>() == id){
            found = true;
            string newStatus;
            cout << "| >> New status: ";
            cin.ignore();
            getline(cin, newStatus);
            target["status"] = newStatus;
            ofstream outFile("TaskList.json");

            if(outFile.is_open()){
                outFile << j.dump(4);
                outFile.close();
                cout << "Task updated successfully! :3" << endl;
            }
            break;
        }
    }
    if(!found)
        cout << "id not found, check list" << endl;
    }else
        cout << "File empty" << endl;
}

int main(){
    cout << R"(    |\__/,|   (`\ )" << "\n" 
         << "  _.|o o  |_   ) )\n"
         << "-(((---(((--------" << endl;
    cout << "+-Welcome to your to-do list!─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─+\n|" << endl;
    cout << "| choose opr number:" << endl;
    cout << "|   1. list tasks" << endl;
    cout << "|   2. add task" << endl;
    cout << "|   3. update status" << endl;
    cout << "|   4. delete task" << endl;
    int opr;
    cout << "|   >> ";
    while(cin >> opr){
        if(opr == 1){
            cout << endl;
            displayTask();
        }else if(opr == 2){
            Task t;
            addTask(t);
        }else if(opr == 3){
            int id;
            cout << "| task id to be updated: ";
            cin >> id;
            updateTask(id);
        }else
            break;
        cout << "| choose opr number:" << endl;
        cout << "|   1. list tasks" << endl;
        cout << "|   2. add task" << endl;
        cout << "|   3. update status" << endl;
        cout << "|   4. delete task" << endl;
        cout << "|   >> ";
    }
}
