-- countries.sql
-- Создание таблицы country
CREATE TABLE country (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(100) NOT NULL,
    capital VARCHAR(100) NOT NULL,
    language VARCHAR(50) NOT NULL,
    population_country INTEGER NOT NULL,
    square_country FLOAT NOT NULL,
    currency VARCHAR(50) NOT NULL,
    head_country VARCHAR(100) NOT NULL
);

-- Создание таблицы region
CREATE TABLE region (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(100) NOT NULL,
    capital_region VARCHAR(100) NOT NULL,
    population_region INTEGER NOT NULL,
    square_region FLOAT NOT NULL,
    country_id INTEGER NOT NULL,
    FOREIGN KEY (country_id) REFERENCES country(id) ON DELETE CASCADE
);

-- Создание таблицы User
CREATE TABLE User (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username VARCHAR(50) NOT NULL UNIQUE,
    password_hash VARCHAR(128) NOT NULL
);

-- Вставка данных в таблицу country
INSERT INTO country (name, capital, language, population_country, square_country, currency, head_country) VALUES
('Беларусь', 'Минск', 'Белорусский', 9400000, 207600, 'Белорусский рубль', 'Александр Лукашенко'),
('Россия', 'Москва', 'Русский', 146000000, 17125191, 'Российский рубль', 'Владимир Путин'),
('Туркменистан', 'Ашхабад', 'Туркменский', 6100000, 488100, 'Туркменский манат', 'Сердар Бердымухамедов'),
('Турция', 'Анкара', 'Турецкий', 85000000, 783562, 'Турецкая лира', 'Реджеп Тайип Эрдоган');

-- Вставка данных в таблицу region
INSERT INTO region (name, capital_region, population_region, square_region, country_id) VALUES
-- Беларусь (country_id = 1)
('Минская область', 'Минск', 1400000, 39854, 1),
('Гродненская область', 'Гродно', 1000000, 25127, 1),
('Брестская область', 'Брест', 1300000, 32786, 1),
-- Россия (country_id = 2)
('Московская область', 'Красногорск', 7800000, 44329, 2),
('Ленинградская область', 'Гатчина', 1900000, 83908, 2),
('Свердловская область', 'Екатеринбург', 4300000, 194307, 2),
-- Туркменистан (country_id = 3)
('Ахалский велаят', 'Анев', 900000, 97300, 3),
('Балканский велаят', 'Балканабат', 500000, 139300, 3),
('Дашогузский велаят', 'Дашогуз', 1400000, 73500, 3),
-- Турция (country_id = 4)
('Стамбул', 'Стамбул', 15500000, 5343, 4),
('Измир', 'Измир', 4400000, 11891, 4),
('Анталья', 'Анталья', 2600000, 20723, 4);

-- Вставка тестового пользователя в таблицу User
INSERT INTO User (username, password_hash) VALUES
('admin', 'admin');
