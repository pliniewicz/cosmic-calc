# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O3 -fopenmp -std=c2x -march=native -I./include
LDFLAGS = -lm -lgsl -lgslcblas -lcjson -fopenmp

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Main target
TARGET = $(BIN_DIR)/cosmic-calc

# Default target
all: directories $(TARGET)

# Create required directories
directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

# Compile object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link executable
$(TARGET): $(OBJ_FILES)
	$(CC) $^ -o $@ $(LDFLAGS)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)/* $(BIN_DIR)/*

.PHONY: all clean run docs directories
