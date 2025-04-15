#ifndef COUNTRY_H
#define COUNTRY_H

#include <sqlite3.h>

void add_country(sqlite3 *db, const char *name, const char *capital, const char *language,
                 int population, float square, const char *currency, const char *head);
void delete_country(sqlite3 *db, int id);
void list_countries(sqlite3 *db);
void list_regions_by_country(sqlite3 *db, const char *country_name);
void avg_population_by_country(sqlite3 *db, const char *country_name);
void total_population(sqlite3 *db);

#endif