#Katalogi
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin

# Nazwa pliku wynikowego
OUTPUT = $(BIN_DIR)/program

# Kompilator
CC = gcc
CFLAGS = -Wall -Wextra -std=c23 -I$(INCLUDE_DIR)

# Pliki źródłowe i obiektowe
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRC))

# Domyślny cel
all: $(OUTPUT)

# Kompilacja programu
$(OUTPUT): $(OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $@

# Kompilacja plików .c do .o w bin/
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Tworzenie katalogu bin, jeśli nie istnieje
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Usuwanie plików obiektowych i programu
clean:
	rm -rf $(BIN_DIR)

