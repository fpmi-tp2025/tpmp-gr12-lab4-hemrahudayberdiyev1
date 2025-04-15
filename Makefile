CC = gcc
CFLAGS = -Iincludes -Wall
LDFLAGS = -lsqlite3
SRC = src/main.c src/auth.c src/database.c src/country.c src/region.c
OBJ = $(SRC:.c=.o)
TARGET = bin/country_app

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean