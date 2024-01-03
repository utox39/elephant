# Your executable name
TARGET = elephant

# Compiler
CC = gcc

# Compilation options
CFLAGS = -O -Wall -W -pedantic -ansi -std=c11

# Source directory
SRC_DIR = src

# Destination directory for objects
BUILD_DIR = build

# List of source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Default rule to build the executable
all: | $(BUILD_DIR) $(BUILD_DIR)/$(TARGET)

# Rule to create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule to build the executable without keeping object files
$(BUILD_DIR)/$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

# Clean up object files and the executable
clean:
	rm -rf $(BUILD_DIR)
