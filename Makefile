# Directory containing source files
SRC_DIR = src
# Directory for the compiled executables
BIN_DIR = .

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude -lpthread

# Default target: compile all executables
all: $(BIN_DIR)/philosophe $(BIN_DIR)/philosophe_tas $(BIN_DIR)/philosophe_tatas $(BIN_DIR)/prodcons $(BIN_DIR)/prodcons_tas $(BIN_DIR)/prodcons_tatas $(BIN_DIR)/readerwriter $(BIN_DIR)/readerwriter_tas $(BIN_DIR)/readerwriter_tatas $(BIN_DIR)/test_and_set_perf $(BIN_DIR)/test_and_test_and_set_perf

# Rule to build each executable

## philosophe
$(BIN_DIR)/philosophe : $(SRC_DIR)/philosophe.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(BIN_DIR)/philosophe_tas : $(SRC_DIR)/philosophe_tas.c $(SRC_DIR)/test_and_set.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/philosophe_tatas : $(SRC_DIR)/philosophe_tatas.c $(SRC_DIR)/test_and_set.c $(SRC_DIR)/test_and_test_and_set.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^


## producer/consumer
$(BIN_DIR)/prodcons : $(SRC_DIR)/prodcons.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(BIN_DIR)/prodcons_tas : $(SRC_DIR)/prodcons_tas.c $(SRC_DIR)/sem_tas.c $(SRC_DIR)/test_and_set.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/prodcons_tatas : $(SRC_DIR)/prodcons_tatas.c $(SRC_DIR)/sem_tatas.c $(SRC_DIR)/test_and_set.c $(SRC_DIR)/test_and_test_and_set.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^


## reader/writer
$(BIN_DIR)/readerwriter : $(SRC_DIR)/readerwriter.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(BIN_DIR)/readerwriter_tas : $(SRC_DIR)/readerwriter_tas.c $(SRC_DIR)/sem_tas.c $(SRC_DIR)/test_and_set.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/readerwriter_tatas : $(SRC_DIR)/readerwriter_tatas.c $(SRC_DIR)/sem_tatas.c $(SRC_DIR)/test_and_set.c $(SRC_DIR)/test_and_test_and_set.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^


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
	rm -f $(BIN_DIR)/philosophe $(BIN_DIR)/philosophe_tas $(BIN_DIR)/philosophe_tatas $(BIN_DIR)/prodcons $(BIN_DIR)/prodcons_tas $(BIN_DIR)/prodcons_tatas $(BIN_DIR)/readerwriter $(BIN_DIR)/readerwriter_tas $(BIN_DIR)/readerwriter_tatas $(BIN_DIR)/test_and_set_perf $(BIN_DIR)/test_and_test_and_set_perf

# Phony targets
.PHONY: all clean
