CC = gcc
CFLAGS = -Wall -Iincludes
LIBS = -lsqlite3
SRC_DIR = src
INC_DIR = includes
BIN_DIR = bin
BUILD_DIR = build
SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/auth.c $(SRC_DIR)/database.c $(SRC_DIR)/country.c $(SRC_DIR)/region.c
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
TARGET = $(BIN_DIR)/country_app

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(OBJECTS) -o $@ $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BIN_DIR)/* $(BUILD_DIR)/*

install-deps:
	sudo apt-get update
	sudo apt-get install -y libsqlite3-dev

rebuild: clean all

.PHONY: all clean install-deps rebuild