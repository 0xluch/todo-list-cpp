#include "opendb.h"

SQLite::Database& getDB(){
    static SQLite::Database db("tasktracker.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    return db;
}

void openDB(){
    auto& db = getDB();
    db.exec(R"(
        CREATE TABLE IF NOT EXISTS folders (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            folder_name TEXT NOT NULL UNIQUE,
            is_system INTEGER NOT NULL DEFAULT 0
            )
        )");
    SQLite::Statement query(db, "INSERT OR IGNORE INTO folders (folder_name, is_system) VALUES (?, ?);");
    query.bind(1, "default");
    query.bind(2, 1);
    query.exec(); 

    db.exec(R"(
        CREATE TABLE IF NOT EXISTS tasks (
            id INTEGER PRIMARY KEY AUTOINCREMENT, 
            title TEXT NOT NULL, 
            status TEXT NOT NULL,
            folder_id INTEGER NOT NULL,
            FOREIGN KEY (folder_id) REFERENCES folders(id)
            )
        )");
}