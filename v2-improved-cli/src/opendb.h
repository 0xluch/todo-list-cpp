#pragma once 
#include <SQLiteCpp/SQLiteCpp.h> 

SQLite::Database& getDB();
void openDB();