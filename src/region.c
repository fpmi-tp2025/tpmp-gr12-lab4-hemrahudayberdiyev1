#include <stdio.h>
#include <sqlite3.h>
#include "region.h"

void add_region(sqlite3 *db, const char *name, const char *capital, int population,
                float square, int country_id) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO region (name, capital_region, population_region, "
                      "square_region, country_id) VALUES (?, ?, ?, ?, ?)";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, capital, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, population);
        sqlite3_bind_double(stmt, 4, square);
        sqlite3_bind_int(stmt, 5, country_id);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            fprintf(stderr, "Error adding region: %s\n", sqlite3_errmsg(db));
        }
        sqlite3_finalize(stmt);
    }
}

void delete_region(sqlite3 *db, int id) {
    sqlite3_stmt *stmt;
    const char *sql = "DELETE FROM region WHERE id = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

void list_regions(sqlite3 *db) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, name, capital_region FROM region";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("ID: %d, Name: %s, Capital: %s\n",
                   sqlite3_column_int(stmt, 0),
                   sqlite3_column_text(stmt, 1),
                   sqlite3_column_text(stmt, 2));
        }
        sqlite3_finalize(stmt);
    }
}