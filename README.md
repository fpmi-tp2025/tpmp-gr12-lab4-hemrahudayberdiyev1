# CountryApp

## Description
CountryApp is a console-based application developed in C for managing information about countries and their regions. It allows users to perform CRUD operations (Create, Read, Update, Delete) on country data (name, capital, language, population, area, currency, head of state) and region data (name, regional capital, population, area). The application uses SQLite to store data and includes user authentication to ensure secure access. Key features include listing regions by country, calculating the average population of regions, and summing the total population of all countries. This project was created as part of the "Mobile Application Programming Technologies" course for the 2024-2025 academic year.

## Installation
Follow these steps to set up and run CountryApp on your local machine:

1. **Clone the repository**:
   ```bash
   git clone https://github.com/your-username/CountryApp.git
   cd CountryApp
   ```

2. **Install dependencies**:
   - GCC: Ubuntu (`sudo apt-get install gcc`), Windows (MinGW), macOS (`xcode-select --install`).
   - SQLite: Ubuntu (`sudo apt-get install libsqlite3-dev`), Windows (`sqlite3.dll` from sqlite.org), macOS (`brew install sqlite`).

3. **Build**:
   ```bash
   make
   ```

4. **Database**:
   - Create `countries.db`:
     ```bash
     sqlite3 countries.db < docs/countries.sql
     ```

## Usage
1. **Run**:
   ```bash
   ./bin/countryapp
   ```

2. **Log in**:
   ```
   Username: admin
   Password: admin
   ```

3. **Menu**:
   ```
   CountryApp Menu:
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
   ```

4. **Example**:
   - List regions (Russia, `country_id=2`):
     ```
     Choice: 7
     Country ID: 2
     ```
     Output:
     ```
     Regions for country ID 2:
     ID | Name               | Capital      | Population | Square
     -----------------------------------------------
     4  | Moscow Oblast      | Krasnogorsk  | 7800000    | 44329.00
     5  | Leningrad Oblast   | Gatchina     | 1900000    | 83908.00
     6  | Sverdlovsk Oblast  | Yekaterinburg | 4300000   | 194307.00
     ```

5. **Docs**:
   - [Wiki](https://github.com/your-username/CountryApp/wiki)
   - Schema: [docs/er-diagram.png](docs/er-diagram.png)
   - Script: [docs/countries.sql](docs/countries.sql)

## Contributing
- **Author**:

- Hemra Hudayberdiyev
- 
- **Help**:
  - Branch: `git checkout -b feature`
  - Commit: `git commit -m "Changes"`
  - Push: `git push origin feature`
  - Submit pull request to `main`.
-
- GitHub .

