# Makefile для компиляции CountryApp

# Компилятор
CC = gcc

# Флаги компиляции
CFLAGS = -Wall -g

# Флаги для линковки SQLite
LDFLAGS = -lsqlite3

# Каталоги
SRC_DIR = src
INCLUDE_DIR = includes
BIN_DIR = bin
BUILD_DIR = build

# Список исходных файлов
SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/auth.c $(SRC_DIR)/database.c $(SRC_DIR)/country.c $(SRC_DIR)/region.c

# Список объектных файлов
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

# Имя исполняемого файла
TARGET = $(BIN_DIR)/countryapp

# Правило по умолчанию
all: $(TARGET)

# Правило для создания исполняемого файла
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# Правило для компиляции объектных файлов
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Очистка
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

# Полная очистка
distclean: clean
	rm -rf $(BIN_DIR) $(BUILD_DIR)

# Указание, что это не файлы
.PHONY: all clean distclean