#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "auth.h"

int authenticate_user(sqlite3* db, const char* username, const char* password) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT password_hash FROM User WHERE username = ?";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* stored_password = (const char*)sqlite3_column_text(stmt, 0);
        if (strcmp(password, stored_password) == 0) {
            sqlite3_finalize(stmt);
            return 1;
        }
    }

    sqlite3_finalize(stmt);
    return 0;
}