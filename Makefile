# Directory containing source files
SRC_DIR = src
# Directory for the compiled executables
BIN_DIR = bin

# Find all .c files in SRC_DIR
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Generate executable names by replacing src/ with bin/ and .c with nothing
EXES = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%,$(SRCS))

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Default target: compile all executables
all: $(EXES)

# Rule to build each executable
$(BIN_DIR)/%: $(SRC_DIR)/%.c
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $@

# Add individual targets for each source file
# Dynamically create rules for individual source files
.PHONY: $(basename $(notdir $(SRCS)))
$(basename $(notdir $(SRCS))): %: $(BIN_DIR)/%
	@echo "Compiled $@ successfully."

# Clean up compiled files
clean:
	rm -rf $(BIN_DIR)

# Phony targets
.PHONY: all clean
