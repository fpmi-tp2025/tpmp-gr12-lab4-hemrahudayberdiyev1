CountryApp
Description
CountryApp is a console application written in C for managing data about countries and their regions. It supports CRUD operations (Create, Read, Update, Delete) for countries (attributes: name, capital, language, population, area, currency, head of state) and regions (attributes: name, regional capital, population, area, linked to a country). The application uses SQLite as its database and implements user authentication for secure access. Key features include listing regions by country, calculating the average population of a country's regions, and computing the total population across all countries. This project was developed as part of the "Mobile Application Programming Technologies" course during the 2024-2025 academic year.
Project Structure
Below is the directory structure of the project:
CountryApp/
├── bin/                # Compiled executables
│   └── countryapp
├── build/              # Object files
├── includes/           # Header files
│   ├── auth.h
│   ├── database.h
│   ├── country.h
│   └── region.h
├── src/                # Source files
│   ├── main.c
│   ├── auth.c
│   ├── database.c
│   ├── country.c
│   └── region.c
├── docs/               # Documentation and diagrams
│   ├── countries.sql
│   ├── er-diagram.png
│   ├── uml-use-case.png
│   ├── uml-class.png
│   ├── uml-activity-login.png
│   ├── uml-activity-add-country.png
│   ├── uml-sequence-add-country.png
│   ├── uml-state-login.png
│   └── uml-deployment.png
├── countries.db        # SQLite database
├── Makefile            # Build automation
├── README.md           # Project documentation
└── .gitignore          # Git ignore file

Installation
To set up and run CountryApp locally, follow these steps:

Clone the repository:
git clone https://github.com/your-username/CountryApp.git
cd CountryApp


Install dependencies:

C Compiler: Ensure GCC or another C compiler is installed.
Ubuntu/Debian:sudo apt-get install gcc


Windows: Install MinGW (http://www.mingw.org/) or use an IDE like Code::Blocks.
macOS: Install Xcode Command Line Tools:xcode-select --install




SQLite: Install the SQLite development library.
Ubuntu/Debian:sudo apt-get install libsqlite3-dev


Windows: Download sqlite3.dll and sqlite3.h from https://www.sqlite.org/download.html and place them in your MinGW include/lib directories or project folder.
macOS:brew install sqlite




SQLite Tool (optional): For database management, install DB Browser for SQLite:
Ubuntu: sudo apt-get install sqlitebrowser
Windows/macOS: Download from https://sqlitebrowser.org/




Compile the project:

Use the provided Makefile:make

This creates the executable bin/countryapp.
Alternatively, compile manually:mkdir -p bin
gcc src/*.c -Iincludes -o bin/countryapp -lsqlite3




Set up the database:

The application requires countries.db in the project root.
If countries.db is missing, generate it using docs/countries.sql:sqlite3 countries.db < docs/countries.sql


The database includes:
Countries: Belarus, Russia, Turkmenistan, Turkey.
Regions: Three regions per country (e.g., Moscow Oblast, Leningrad Oblast, Sverdlovsk Oblast for Russia).
User: Test account (admin/admin).





Usage

Launch the application:
./bin/countryapp


Authenticate:

Log in using the default credentials:Username: admin
Password: admin


Note: In a production environment, replace the default user with a secure password (hashed, e.g., using SHA-256).


Navigate the menu:

After login, the main menu is displayed:CountryApp Menu:
1. Add country
2. Delete country
3. Update country
4. Add region
5. Delete region
6. Update region
7. List regions by country
8. Average population by country
9. Total population
10. Exit


Enter a number (1–10) to select an option and follow the prompts.


Examples:

Add a country:
Choice: 1
Name: Russia
Capital: Moscow
Language: Russian
Population: 146000000
Square: 17125191
Currency: Russian Rubles
Head: Vladimir Putin

Output:
Country added: Russia


Add a region (e.g., for Russia, assuming country_id=2):
Choice: 4
Name: Moscow Oblast
Capital: Krasnogorsk
Population: 7800000
Square: 44329
Country ID: 2

Output:
Region added: Moscow Oblast


Update a country (e.g., Belarus, country_id=1):
Choice: 3
Country ID: 1
Name: Belarus
Capital: Minsk
Language: Belarusian
Population: 9500000
Square: 207600
Currency: Belarusian Rubles
Head: Alexander Lukashenko

Output:
Country updated: ID 1


List regions (e.g., for Russia, country_id=2):
Choice: 7
Country ID: 2

Output:
Regions for country ID 2:
ID | Name               | Capital      | Population | Square
-----------------------------------------------
4  | Московская область | Красногорск  | 7800000    | 44329.00
5  | Ленинградская область | Гатчина    | 1900000    | 83908.00
6  | Свердловская область | Екатеринбург | 4300000  | 194307.00


Calculate average population (e.g., for Russia):
Choice: 8
Country ID: 2

Output:
Average population for country ID 2: 4666666.67


Calculate total population:
Choice: 9

Output:
Total population: 245500000




Documentation:

Wiki: Detailed specifications, including functional requirements, UML diagrams, and database schema, are available in the Project Wiki.
Database Schema: View the ER-diagram at docs/er-diagram.png.
SQL Script: The database creation script is at docs/countries.sql.
UML Diagrams: Available in the wiki under "Specification" or directly in docs/:
Use Case: uml-use-case.png
Class: uml-class.png
Activity (Login): uml-activity-login.png
Activity (Add Country): uml-activity-add-country.png
Sequence (Add Country): uml-sequence-add-country.png
State (Login): uml-state-login.png
Deployment: uml-deployment.png





Contributing

Author: [Your Name] — designed and implemented the application, including authentication, database operations, CRUD functionality, and query processing.
How to Contribute:
Fork or Branch:
Create a new branch for your feature or bug fix:git checkout -b feature/your-feature-name


Make changes and commit:git commit -m "Describe your changes"


Push to your branch:git push origin feature/your-feature-name


Open a pull request to the main branch on GitHub.


Coding Guidelines:
Follow the existing code style (e.g., 4-space indentation, clear function names).
Add comments for complex logic.
Update documentation (wiki or README) for new features.


Issues:
Report bugs or suggest enhancements by creating an issue in the repository.
Include steps to reproduce bugs and expected behavior.


Contact:
GitHub Issues: https://github.com/your-username/CountryApp/issues





License
This project is licensed under the MIT License. See LICENSE for details.
Notes

This is an academic project and may evolve with additional features or optimizations.
For troubleshooting (e.g., compilation errors, database issues), refer to the wiki's "Additional Specification" section or create an issue.
Sample data includes countries (Belarus, Russia, Turkmenistan, Turkey) and their regions, as specified in docs/countries.sql.

