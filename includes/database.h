#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

sqlite3* init_db(const char *db_name);
void close_db(sqlite3 *db);

#endif