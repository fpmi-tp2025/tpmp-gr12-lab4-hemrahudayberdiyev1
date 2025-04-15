#ifndef AUTH_H
#define AUTH_H

#include <sqlite3.h>

int authenticate_user(sqlite3 *db, const char *username, const char *password);
int register_user(sqlite3 *db, const char *username, const char *password);

#endif