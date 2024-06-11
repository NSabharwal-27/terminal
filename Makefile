CC = gcc
CFLAGS = -Wall -Iinclude

SRC_DIRS := ./src
INC_DIRS := ./include
BIN_DIR := ./bin

SRCS := $(SRC_DIRS)/main.c $(SRC_DIRS)/queue.c
OBJS := $(patsubst $(SRC_DIRS)/%.c, $(BIN_DIR)/%.o, $(SRCS))

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main

$(BIN_DIR)/%.o: $(SRC_DIRS)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

.PHONY: clean
clean:
	rm -rf $(BIN_DIR) main