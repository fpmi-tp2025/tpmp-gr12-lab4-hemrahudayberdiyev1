#include <stdio.h>
#include <sqlite3.h>
#include "country.h"

void add_country(sqlite3* db, const char* name, const char* capital, const char* language,
                 int population, float square, const char* currency, const char* head) {
    const char* sql = "INSERT INTO country (name, capital, language, population_country, square_country, currency, head_country) "
                      "VALUES (?, ?, ?, ?, ?, ?, ?)";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, capital, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, language, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, population);
    sqlite3_bind_double(stmt, 5, square);
    sqlite3_bind_text(stmt, 6, currency, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, head, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Country added: %s\n", name);
    }

    sqlite3_finalize(stmt);
}

void delete_country(sqlite3* db, int id) {
    const char* sql = "DELETE FROM country WHERE id = ?";
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
        printf("Country deleted: ID %d\n", id);
    }

    sqlite3_finalize(stmt);
}

void update_country(sqlite3* db, int id, const char* name, const char* capital, const char* language,
                    int population, float square, const char* currency, const char* head) {
    const char* sql = "UPDATE country SET name = ?, capital = ?, language = ?, population_country = ?, "
                      "square_country = ?, currency = ?, head_country = ? WHERE id = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, capital, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, language, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, population);
    sqlite3_bind_double(stmt, 5, square);
    sqlite3_bind_text(stmt, 6, currency, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 7, head, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 8, id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Country updated: ID %d\n", id);
    }

    sqlite3_finalize(stmt);
}