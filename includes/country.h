#ifndef COUNTRY_H
#define COUNTRY_H

void add_country(sqlite3* db, const char* name, const char* capital, const char* language,
                 int population, float square, const char* currency, const char* head);
void delete_country(sqlite3* db, int id);

#endif