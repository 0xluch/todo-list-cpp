#include "opendb.h"
#include <SQLiteCpp/SQLiteCpp.h> 

void openDB(){
    SQLite::Database db("tasktracker.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        db.exec(R"(
            CREATE TABLE IF NOT EXISTS tasks (
                id INTEGER PRIMARY KEY AUTOINCREMENT, 
                title TEXT NOT NULL, 
                status TEXT NOT NULL,
                folder TEXT NOT NULL
                )
            )");
}
    