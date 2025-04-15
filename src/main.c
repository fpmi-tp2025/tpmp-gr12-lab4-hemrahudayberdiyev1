#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "auth.h"
#include "database.h"
#include "country.h"
#include "region.h"

void print_menu() {
    printf("\nCountryApp Menu:\n");
    printf("1. Add Country\n");
    printf("2. Delete Country\n");
    printf("3. List Countries\n");
    printf("4. Add Region\n");
    printf("5. Delete Region\n");
    printf("6. List Regions\n");
    printf("7. List Regions by Country\n");
    printf("8. Average Population by Country\n");
    printf("9. Total Population\n");
    printf("10. Register New User\n");
    printf("11. Exit\n");
    printf("Enter choice: ");
}

int main() {
    sqlite3 *db = init_db("countries.db");
    if (!db) return 1;

    // Аутентификация
    char username[50], password[128];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (!authenticate_user(db, username, password)) {
        printf("Authentication failed. Try registering.\n");
        close_db(db);
        return 1;
    }

    // Основной цикл меню
    int choice;
    char name[100], capital[100], language[50], currency[50], head[100];
    int population, country_id, id;
    float square;

    while (1) {
        print_menu();
        scanf("%d", &choice);
        getchar(); // Очистка буфера

        switch (choice) {
            case 1: // Add Country
                printf("Enter name: ");
                fgets(name, sizeof(name), stdin); name[strcspn(name, "\n")] = 0;
                printf("Enter capital: ");
                fgets(capital, sizeof(capital), stdin); capital[strcspn(capital, "\n")] = 0;
                printf("Enter language: ");
                fgets(language, sizeof(language), stdin); language[strcspn(language, "\n")] = 0;
                printf("Enter population: ");
                scanf("%d", &population);
                printf("Enter square: ");
                scanf("%f", &square);
                getchar();
                printf("Enter currency: ");
                fgets(currency, sizeof(currency), stdin); currency[strcspn(currency, "\n")] = 0;
                printf("Enter head: ");
                fgets(head, sizeof(head), stdin); head[strcspn(head, "\n")] = 0;
                add_country(db, name, capital, language, population, square, currency, head);
                break;

            case 2: // Delete Country
                printf("Enter country ID to delete: ");
                scanf("%d", &id);
                delete_country(db, id);
                break;

            case 3: // List Countries
                list_countries(db);
                break;

            case 4: // Add Region
                printf("Enter region name: ");
                fgets(name, sizeof(name), stdin); name[strcspn(name, "\n")] = 0;
                printf("Enter region capital: ");
                fgets(capital, sizeof(capital), stdin); capital[strcspn(capital, "\n")] = 0;
                printf("Enter population: ");
                scanf("%d", &population);
                printf("Enter square: ");
                scanf("%f", &square);
                printf("Enter country ID: ");
                scanf("%d", &country_id);
                getchar();
                add_region(db, name, capital, population, square, country_id);
                break;

            case 5: // Delete Region
                printf("Enter region ID to delete: ");
                scanf("%d", &id);
                delete_region(db, id);
                break;

            case 6: // List Regions
                list_regions(db);
                break;

            case 7: // List Regions by Country
                printf("Enter country name: ");
                fgets(name, sizeof(name), stdin); name[strcspn(name, "\n")] = 0;
                list_regions_by_country(db, name);
                break;

            case 8: // Average Population by Country
                printf("Enter country name: ");
                fgets(name, sizeof(name), stdin); name[strcspn(name, "\n")] = 0;
                avg_population_by_country(db, name);
                break;

            case 9: // Total Population
                total_population(db);
                break;

            case 10: // Register New User
                printf("Enter new username: ");
                fgets(username, sizeof(username), stdin); username[strcspn(username, "\n")] = 0;
                printf("Enter new password: ");
                fgets(password, sizeof(password), stdin); password[strcspn(password, "\n")] = 0;
                if (register_user(db, username, password)) {
                    printf("User registered successfully.\n");
                } else {
                    printf("Registration failed.\n");
                }
                break;

            case 11: // Exit
                close_db(db);
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    close_db(db);
    return 0;
}