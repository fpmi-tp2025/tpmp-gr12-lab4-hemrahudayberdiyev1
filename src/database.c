#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "database.h"

sqlite3* init_db(const char* db_name) {
    sqlite3* db;
    int rc = sqlite3_open(db_name, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }
    return db;
}

void close_db(sqlite3* db) {
    if (db) {
        sqlite3_close(db);
    }
}