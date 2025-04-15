#include <stdio.h>
#include <sqlite3.h>
#include "country.h"

void add_country(sqlite3 *db, const char *name, const char *capital, const char *language,
                 int population, float square, const char *currency, const char *head) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO country (name, capital, language, population_country, "
                      "square_country, currency, head_country) VALUES (?, ?, ?, ?, ?, ?, ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, capital, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, language, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 4, population);
        sqlite3_bind_double(stmt, 5, square);
        sqlite3_bind_text(stmt, 6, currency, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 7, head, -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            fprintf(stderr, "Error adding country: %s\n", sqlite3_errmsg(db));
        }
        sqlite3_finalize(stmt);
    }
}

void delete_country(sqlite3 *db, int id) {
    sqlite3_stmt *stmt;
    const char *sql = "DELETE FROM country WHERE id = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }
}

void list_countries(sqlite3 *db) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, name, capital FROM country";
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

void list_regions_by_country(sqlite3 *db, const char *country_name) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT r.name, r.capital_region FROM region r "
                      "JOIN country c ON r.country_id = c.id WHERE c.name = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, country_name, -1, SQLITE_STATIC);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("Region: %s, Capital: %s\n",
                   sqlite3_column_text(stmt, 0),
                   sqlite3_column_text(stmt, 1));
        }
        sqlite3_finalize(stmt);
    }
}

void avg_population_by_country(sqlite3 *db, const char *country_name) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT AVG(r.population_region) FROM region r "
                      "JOIN country c ON r.country_id = c.id WHERE c.name = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, country_name, -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("Average population in %s's regions: %.2f\n",
                   country_name, sqlite3_column_double(stmt, 0));
        }
        sqlite3_finalize(stmt);
    }
}

void total_population(sqlite3 *db) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT SUM(population_country) FROM country";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("Total population across all countries: %d\n",
                   sqlite3_column_int(stmt, 0));
        }
        sqlite3_finalize(stmt);
    }
}