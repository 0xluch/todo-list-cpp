#include "opendb.h"

SQLite::Database& getDB(){
    SQLite::Database db("tasktracker.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
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
    