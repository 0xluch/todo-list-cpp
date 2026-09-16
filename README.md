# Todo Tracker

A simple todo tracker application built with **C++**, developed as a learning project.

The project started as a small file-based CLI application and evolved into a more structured version using **SQLite** for persistent storage and **folders** for organizing tasks (v3 coming soon).

---

## 📌 Versions

### V1 — Simple CLI

The first version focuses on the fundamentals of building a todo application in C++.

**Storage:** JSON

**Main features:**

* Add tasks
* List tasks
* Update task status
* Update task title
* Delete tasks
* Save tasks to a JSON file
* Basic project structure

V1 was mainly an exercise in **C++ file handling, structures, functions, and separating code into multiple files**.

---

### V2 — Improved CLI

V2 rebuilds the application around a **SQLite database** instead of a JSON file.

**Storage:** SQLite

**Main features:**

* Add tasks
* List tasks
* Update task status
* Update task title
* Delete tasks
* Create folders
* List folders
* Rename folders
* Delete folders
* Assign tasks to folders
* Protected default system folder
* Input validation
* Persistent SQLite storage

V2 also introduces a relational database structure where tasks reference folders using a **foreign key**.

---

## 🆚 V1 vs V2

| Feature              | V1     | V2        |
|----------------------|--------|-----------|
| Language             | C++    | C++       |
| Interface            | CLI    | CLI       |
| Storage              | JSON   | SQLite    |
| Input validation     | Basic  | Improved  |

---

## 🛠️ Technologies

### V1

* C++
* C++17
* [nlohmann/json](https://github.com/nlohmann/json)

### V2

* C++
* C++17
* CMake
* SQLite
* SQLiteCpp

---

## 📁 Project Structure

```text
todo-cpp/
│
├── README.md
├── LICENSE
├── .gitignore
│
├── v1-simple-cli/
│   ├── main.cpp
│   ├── src/
│   │   ├── task.h
│   │   ├── task.cpp
│   │   ├── taskops.h
│   │   ├── taskops.cpp
│   │   ├── storage.h
│   │   ├── storage.cpp
│   │   ├── ui.h
│   │   └── ui.cpp
│   └── TaskList.json
│
├── v2-improved-cli/
│   ├── main.cpp
│   ├── CMakeLists.txt
│   └── src/
│       ├── taskops.h
│       ├── taskops.cpp
│       ├── folderops.h
│       ├── folderops.cpp
│       ├── opendb.h
│       ├── opendb.cpp
│       ├── ui.h
│       └── ui.cpp
│
└── v3-gui/ (coming soon)
```

---

## 🚀 Getting Started

### V1

Navigate to the V1 directory and compile:

```bash
g++ -std=c++17 main.cpp src/*.cpp -o todo
```

Then run:

```bash
./todo
```

V1 requires the **nlohmann/json** library.

---

### V2

V2 uses CMake.

From the V2 directory:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Then run the generated executable.

```bash
./todo
```

The application creates its SQLite database automatically when it runs.

---

## 🗄️ V2 Database Structure

V2 uses two main tables.

### Folders

```text
folders
├── id
├── folder_name
└── is_system
```

The default folder is marked as a system folder and is protected from being renamed or deleted.

### Tasks

```text
tasks
├── id
├── title
├── status
└── folder_id
```

`folder_id` references the corresponding folder in the `folders` table.

---

## 🎯 What I Learned

This project is mainly a way for me to practice and improve my C++ skills.

Through V1 and V2, I worked with:

* C++17
* Header/source separation
* Structs
* Functions and references
* File handling
* JSON
* SQLite
* SQL CRUD operations
* Prepared statements
* Foreign keys
* SQL JOINs
* Input validation
* CMake
* Basic project organization

---

## 📜 License

See [LICENSE](LICENSE).
