#ifndef REGION_H
#define REGION_H

#include <sqlite3.h>

void add_region(sqlite3 *db, const char *name, const char *capital, int population,
                float square, int country_id);
void delete_region(sqlite3 *db, int id);
void list_regions(sqlite3 *db);

#endif