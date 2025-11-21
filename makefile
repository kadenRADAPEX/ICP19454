# Compiler and flags
CC      := gcc
CFLAGS  := -Wall -Wextra -O2 -g

# Directories
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
EXEC_NAME := exec

# Collect all source files in src/
SRCS := $(wildcard $(SRC_DIR)/*.c)

# Map source files to object files in build/
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Final executable
TARGET := $(BIN_DIR)/$(EXEC_NAME)

# Default rule
all: $(TARGET)

# Link step
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ -lm

# Rule to build object files inside build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure build / bin directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean up
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean