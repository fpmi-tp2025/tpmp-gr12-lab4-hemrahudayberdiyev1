#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "auth.h"
#include "database.h"
#include "country.h"
#include "region.h"

void print_menu() {
    printf("\nCountryApp Menu:\n");
    printf("1. Add country\n");
    printf("2. Delete country\n");
    printf("3. Update country\n");
    printf("4. Add region\n");
    printf("5. Delete region\n");
    printf("6. Update region\n");
    printf("7. List regions by country\n");
    printf("8. Average population by country\n");
    printf("9. Total population\n");
    printf("10. Exit\n");
    printf("Enter choice: ");
}

void list_regions(sqlite3* db, int country_id) {
    const char* sql = "SELECT id, name, capital_region, population_region, square_region "
                      "FROM region WHERE country_id = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_int(stmt, 1, country_id);
    printf("\nRegions for country ID %d:\n", country_id);
    printf("ID | Name | Capital | Population | Square\n");
    printf("-------------------------------------------\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("%d | %s | %s | %d | %.2f\n",
               sqlite3_column_int(stmt, 0),
               sqlite3_column_text(stmt, 1),
               sqlite3_column_text(stmt, 2),
               sqlite3_column_int(stmt, 3),
               sqlite3_column_double(stmt, 4));
    }

    sqlite3_finalize(stmt);
}

void avg_population(sqlite3* db, int country_id) {
    const char* sql = "SELECT AVG(population_region) FROM region WHERE country_id = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_int(stmt, 1, country_id);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("Average population for country ID %d: %.2f\n",
               country_id, sqlite3_column_double(stmt, 0));
    } else {
        printf("No regions found for country ID %d\n", country_id);
    }

    sqlite3_finalize(stmt);
}

void total_population(sqlite3* db) {
    const char* sql = "SELECT SUM(population_country) FROM country";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("Total population: %lld\n", sqlite3_column_int64(stmt, 0));
    } else {
        printf("No countries found\n");
    }

    sqlite3_finalize(stmt);
}

int main() {
    sqlite3* db = init_db("countries.db");
    if (!db) {
        fprintf(stderr, "Failed to initialize database\n");
        return 1;
    }

    char username[50], password[50];
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    getchar(); // Очистка буфера

    if (!authenticate_user(db, username, password)) {
        printf("Authentication failed\n");
        close_db(db);
        return 1;
    }

    int choice, id, population, country_id;
    float square;
    char name[100], capital[100], language[50], currency[50], head[100];

    while (1) {
        print_menu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: // Add country
                printf("Name: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = 0;
                printf("Capital: ");
                fgets(capital, 100, stdin);
                capital[strcspn(capital, "\n")] = 0;
                printf("Language: ");
                fgets(language, 50, stdin);
                language[strcspn(language, "\n")] = 0;
                printf("Population: ");
                scanf("%d", &population);
                printf("Square: ");
                scanf("%f", &square);
                getchar();
                printf("Currency: ");
                fgets(currency, 50, stdin);
                currency[strcspn(currency, "\n")] = 0;
                printf("Head: ");
                fgets(head, 100, stdin);
                head[strcspn(head, "\n")] = 0;
                add_country(db, name, capital, language, population, square, currency, head);
                break;

            case 2: // Delete country
                printf("Country ID: ");
                scanf("%d", &id);
                delete_country(db, id);
                break;

            case 3: // Update country
                printf("Country ID: ");
                scanf("%d", &id);
                getchar();
                printf("Name: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = 0;
                printf("Capital: ");
                fgets(capital, 100, stdin);
                capital[strcspn(capital, "\n")] = 0;
                printf("Language: ");
                fgets(language, 50, stdin);
                language[strcspn(language, "\n")] = 0;
                printf("Population: ");
                scanf("%d", &population);
                printf("Square: ");
                scanf("%f", &square);
                getchar();
                printf("Currency: ");
                fgets(currency, 50, stdin);
                currency[strcspn(currency, "\n")] = 0;
                printf("Head: ");
                fgets(head, 100, stdin);
                head[strcspn(head, "\n")] = 0;
                update_country(db, id, name, capital, language, population, square, currency, head);
                break;

            case 4: // Add region
                printf("Name: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = 0;
                printf("Capital: ");
                fgets(capital, 100, stdin);
                capital[strcspn(capital, "\n")] = 0;
                printf("Population: ");
                scanf("%d", &population);
                printf("Square: ");
                scanf("%f", &square);
                printf("Country ID: ");
                scanf("%d", &country_id);
                getchar();
                add_region(db, name, capital, population, square, country_id);
                break;

            case 5: // Delete region
                printf("Region ID: ");
                scanf("%d", &id);
                delete_region(db, id);
                break;

            case 6: // Update region
                printf("Region ID: ");
                scanf("%d", &id);
                getchar();
                printf("Name: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = 0;
                printf("Capital: ");
                fgets(capital, 100, stdin);
                capital[strcspn(capital, "\n")] = 0;
                printf("Population: ");
                scanf("%d", &population);
                printf("Square: ");
                scanf("%f", &square);
                printf("Country ID: ");
                scanf("%d", &country_id);
                getchar();
                update_region(db, id, name, capital, population, square, country_id);
                break;

            case 7: // List regions
                printf("Country ID: ");
                scanf("%d", &country_id);
                list_regions(db, country_id);
                break;

            case 8: // Average population
                printf("Country ID: ");
                scanf("%d", &country_id);
                avg_population(db, country_id);
                break;

            case 9: // Total population
                total_population(db);
                break;

            case 10: // Exit
                printf("Exiting...\n");
                close_db(db);
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }

    close_db(db);
    return 0;
}