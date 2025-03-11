#Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c23
TEST_FLAGS = -DTEST  # Define TEST flag

# Directories
SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = include

# Files
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRC))
OUTPUT = $(BIN_DIR)/program

# Default compilation (without tests)
all: $(OUTPUT)

$(OUTPUT): $(OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Enable test compilation
test: CFLAGS += $(TEST_FLAGS)
test: clean all  # Recompile everything with TEST flag

# Create bin directory if it doesn’t exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean build files
clean:
	rm -rf $(BIN_DIR)

