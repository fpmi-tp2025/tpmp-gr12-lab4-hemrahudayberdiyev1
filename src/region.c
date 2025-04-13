#include <stdio.h>
#include <sqlite3.h>
#include "region.h"

void add_region(sqlite3* db, const char* name, const char* capital, int population,
                float square, int country_id) {
    const char* sql = "INSERT INTO region (name, capital_region, population_region, square_region, country_id) "
                      "VALUES (?, ?, ?, ?, ?)";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, capital, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, population);
    sqlite3_bind_double(stmt, 4, square);
    sqlite3_bind_int(stmt, 5, country_id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Region added: %s\n", name);
    }

    sqlite3_finalize(stmt);
}

void delete_region(sqlite3* db, int id) {
    const char* sql = "DELETE FROM region WHERE id = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_int(stmt, 1, id);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Region deleted: ID %d\n", id);
    }

    sqlite3_finalize(stmt);
}

void update_region(sqlite3* db, int id, const char* name, const char* capital,
                   int population, float square, int country_id) {
    const char* sql = "UPDATE region SET name = ?, capital_region = ?, population_region = ?, "
                      "square_region = ?, country_id = ? WHERE id = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, capital, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, population);
    sqlite3_bind_double(stmt, 4, square);
    sqlite3_bind_int(stmt, 5, country_id);
    sqlite3_bind_int(stmt, 6, id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Region updated: ID %d\n", id);
    }

    sqlite3_finalize(stmt);
}