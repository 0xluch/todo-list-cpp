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

void saveTasks(const json& listJ){
    ofstream outFile("TaskList.json");
    if(outFile.is_open()){
        outFile << listJ.dump(4);
        outFile.close();
        cout << "| Done :3" << endl;
    }else
        cout << "error...2" << endl;
}

json loadTasks(){
    json listJ = json::array();
    ifstream file("TaskList.json");
    if (file.is_open()){
        if(file.peek() == ifstream::traits_type::eof())
            cout << "| Empty file" << endl;
        else
            file >> listJ;
        file.close();
    }
    return listJ;
}

void displayTask(){
    json listJ = loadTasks();
    
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

string status(){
    int opt;
    cout << "| 1. Completed: " << endl;
    cout << "| 2. In-progress: " << endl;
    cout << "| >> ";
    cin >> opt;
    if(opt == 1)
        return "Completed";
    if(opt == 2)
        return "In-progress";
    else{
        cout << "| unvalid option, try again." << endl;
        return status(); 
    }
}

void addTask(Task t){
    cout << "| title: ";
    cin.ignore();
    getline(cin, t.title);
    cout << "| Choose status: " << endl;
    t.status = status();
    json listJ = loadTasks();

    int size = 1;
    if(!listJ.empty()){
        int maxId = 0;
        for(const auto& element : listJ){
            if(element.contains("id"))
                maxId = max(maxId, element["id"].get<int>());
        }
        size += maxId;
    }
    t.id = size;
    json j;
    to_json (j, t);
    listJ.push_back(j);
    saveTasks(listJ);
}

void updateTask(int& id){
    json j = loadTasks();
    bool found = false;
    for (auto& target : j){
        if(target.contains("id") && target["id"].get<int>() == id){
            found = true;
            cout << "| New status: " << endl;
            string newStatus = status();
            target["status"] = newStatus;
            saveTasks(j);
            break;
        }
    }
    if(!found)
        cout << "id not found, check list" << endl;
}

void deleteTask(int& id){
    json j = loadTasks();
    bool found = false;
    for (auto it = j.begin(); it != j.end(); ){
        if(it->contains("id") && (*it)["id"].get<int>() == id){
            found = true;
            cout << "| task found... ";
            it = j.erase(it);
            saveTasks(j);
            break;
        }else
            ++it;
    }
    if(!found)
        cout << "id not found, check list" << endl;
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
    cout << "|   0. exit" << endl;
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
        }else if(opr == 4){
            int id;
            cout << "| task id to be deleted: ";
            cin >> id;
            deleteTask(id);
        }else
            break;
        cout << "| choose opr number:" << endl;
        cout << "|   1. list tasks" << endl;
        cout << "|   2. add task" << endl;
        cout << "|   3. update status" << endl;
        cout << "|   4. delete task" << endl;
        cout << "|   0. exit" << endl;
        cout << "|   >> ";
    }
}
