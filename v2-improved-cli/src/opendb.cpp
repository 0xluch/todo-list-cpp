#include "opendb.h"

SQLite::Database& getDB(){
    static SQLite::Database db("tasktracker.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    return db;
}

void openDB(){
    auto& db = getDB();
    db.exec(R"(
        CREATE TABLE IF NOT EXISTS tasks (
            id INTEGER PRIMARY KEY AUTOINCREMENT, 
            title TEXT NOT NULL, 
            status TEXT NOT NULL,
            folder TEXT NOT NULL
            )
        )");
}

void openFDB(){
    auto& db = getDB();
    db.exec(R"(
        CREATE TABLE IF NOT EXISTS folders (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            folder TEXT UNIQUE
            )
        )");
    SQLite::Statement query(db, "INSERT OR IGNORE INTO folders (folder) VALUES (?);");
    query.bind(1, "default");
    query.exec(); 
}