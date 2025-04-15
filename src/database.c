#include <stdio.h>
#include <sqlite3.h>
#include "database.h"

sqlite3* init_db(const char *db_name) {
    sqlite3 *db;
    if (sqlite3_open(db_name, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    // Создание таблиц
    const char *sql = 
        "CREATE TABLE IF NOT EXISTS user ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username VARCHAR(50) NOT NULL, "
        "password_hash VARCHAR(128) NOT NULL);"
        "CREATE TABLE IF NOT EXISTS country ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name VARCHAR(100), "
        "capital VARCHAR(100), "
        "language VARCHAR(50), "
        "population_country INTEGER, "
        "square_country FLOAT, "
        "currency VARCHAR(50), "
        "head_country VARCHAR(100));"
        "CREATE TABLE IF NOT EXISTS region ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name VARCHAR(100), "
        "capital_region VARCHAR(100), "
        "population_region INTEGER, "
        "square_region FLOAT, "
        "country_id INTEGER, "
        "FOREIGN KEY (country_id) REFERENCES country(id));";

    char *err_msg = 0;
    if (sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return NULL;
    }

    // Вставка начальных данных
    const char *init_data = 
        "INSERT OR IGNORE INTO country (name, capital, language, population_country, square_country, currency, head_country) VALUES "
        "('Belarus', 'Minsk', 'Belarusian', 9400000, 207600, 'BYN', 'Alexander Lukashenko'),"
        "('Russia', 'Moscow', 'Russian', 146000000, 17125191, 'RUB', 'Vladimir Putin'),"
        "('Turkmenistan', 'Ashgabat', 'Turkmen', 6200000, 488100, 'TMT', 'Serdar Berdimuhamedow'),"
        "('Turkey', 'Ankara', 'Turkish', 85000000, 783562, 'TRY', 'Recep Tayyip Erdogan');"
        "INSERT OR IGNORE INTO region (name, capital_region, population_region, square_region, country_id) VALUES "
        "('Minsk Region', 'Minsk', 1400000, 39800, 1),"
        "('Gomel Region', 'Gomel', 1300000, 40400, 1),"
        "('Moscow Region', 'Moscow', 7500000, 44300, 2),"
        "('Leningrad Region', 'Gatchina', 1800000, 83900, 2),"
        "('Tatarstan', 'Kazan', 3900000, 68000, 2),"
        "('Ahal Region', 'Anaw', 850000, 97160, 3),"
        "('Balkan Region', 'Balkanabat', 500000, 139300, 3),"
        "('Istanbul Region', 'Istanbul', 15000000, 5343, 4),"
        "('Izmir Region', 'Izmir', 4300000, 11891, 4);";

    if (sqlite3_exec(db, init_data, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return NULL;
    }

    return db;
}

void close_db(sqlite3 *db) {
    sqlite3_close(db);
}