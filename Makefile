# Directory containing source files
SRC_DIR = src
# Directory for the compiled executables
BIN_DIR = bin

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude

# Default target: compile all executables
all: $(BIN_DIR)/philosophe $(BIN_DIR)/prodcons $(BIN_DIR)/readerwriter $(BIN_DIR)/test_and_set_perf $(BIN_DIR)/test_and_test_and_set_perf

# Rule to build each executable
$(BIN_DIR)/philosophe : $(SRC_DIR)/philosophe.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(BIN_DIR)/prodcons : $(SRC_DIR)/prodcons.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(BIN_DIR)/readerwriter : $(SRC_DIR)/readerwriter.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(BIN_DIR)/test_and_set : $(SRC_DIR)/test_and_set.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(BIN_DIR)/test_and_set_perf : $(SRC_DIR)/test_and_set_perf.c $(SRC_DIR)/test_and_set.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/test_and_test_and_set_perf : $(SRC_DIR)/test_and_test_and_set_perf.c $(SRC_DIR)/test_and_test_and_set.c $(SRC_DIR)/test_and_set.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

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
