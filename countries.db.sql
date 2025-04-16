-- Создание таблиц
CREATE TABLE country (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(100) NOT NULL,
    capital VARCHAR(100),
    language VARCHAR(50),
    population_country INTEGER,
    square_country REAL,
    currency VARCHAR(50),
    head_country VARCHAR(100)
);

CREATE TABLE region (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(100) NOT NULL,
    capital_region VARCHAR(100),
    population_region INTEGER,
    square_region REAL,
    country_id INTEGER,
    FOREIGN KEY (country_id) REFERENCES country(id) ON DELETE CASCADE
);

CREATE TABLE user (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username VARCHAR(50) NOT NULL UNIQUE,
    password_hash VARCHAR(128) NOT NULL
);

-- Наполнение данными
INSERT INTO user (username, password_hash)
VALUES ('admin', 'admin123'),
       ('user1', 'user123');

INSERT INTO country (name, capital, language, population_country, square_country, currency, head_country)
VALUES ('Belarus', 'Minsk', 'Belarusian, Russian', 9400000, 207600.0, 'BYN', 'President Lukashenko'),
       ('China', 'Beijing', 'Mandarin', 1400000000, 9596961.0, 'CNY', 'President Xi Jinping'),
       ('Russia', 'Moscow', 'Russian', 146000000, 17125191.0, 'RUB', 'President Putin');

INSERT INTO region (name, capital_region, population_region, square_region, country_id)
VALUES ('Minsk Region', 'Minsk', 1400000, 39800.0, 1),
       ('Gomel Region', 'Gomel', 1400000, 40400.0, 1),
       ('Guangdong', 'Guangzhou', 113000000, 179800.0, 2),
       ('Sichuan', 'Chengdu', 83400000, 485000.0, 2),
       ('Moscow Region', 'Moscow', 7500000, 44300.0, 3),
       ('Leningrad Region', 'Gatchina', 1800000, 83900.0, 3);
