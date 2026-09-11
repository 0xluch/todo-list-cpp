# Todo CLI (V1)

A simple command-line todo list written in C++.

This is **Version 1** of the project — focused on file handling and clean structure.

## Features

- Add tasks
- List tasks
- Update task status (Completed / In-progress / Pending)
- Update task title
- Delete tasks
- Data is saved in `TaskList.json`

## Project Structure
```
todo-cpp/
├── .gitignore
├── README.md
├── LICENSE
├── v1-simple-cli/
│   ├── main.cpp
│   ├── task.h / task.cpp
│   ├── storage.h / storage.cpp
│   ├── taskops.h / taskops.cpp
│   ├── ui.h / ui.cpp
│   └── TaskList.json
├── v2-improved-cli/
│   └── (comming soon)
└── v3-gui/
    └── (comming soon)
```

## Requirements

- C++17 or higher
- [nlohmann/json](https://github.com/nlohmann/json)

## How to Compile & Run

```bash
g++ -std=c++17 *.cpp -o todo
./todo
