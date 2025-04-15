#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "auth.h"

// Простая имитация хеширования пароля (в реальном проекте использовать bcrypt или подобное)
static char* simple_hash(const char *password) {
    static char hash[128];
    snprintf(hash, sizeof(hash), "%s_hashed", password); // Заглушка
    return hash;
}

int authenticate_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT password_hash FROM user WHERE username = ?";
    int result = 0;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const char *stored_hash = (const char *)sqlite3_column_text(stmt, 0);
            if (strcmp(stored_hash, simple_hash(password)) == 0) {
                result = 1; // Успешная аутентификация
            }
        }
        sqlite3_finalize(stmt);
    }
    return result;
}

int register_user(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO user (username, password_hash) VALUES (?, ?)";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, simple_hash(password), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            sqlite3_finalize(stmt);
            return 1; // Успешная регистрация
        }
        sqlite3_finalize(stmt);
    }
    return 0;
}