CC = gcc
CFLAGS = -Wall

SRC_DIRS := ./src

main: $(SRC_DIRS)/main.c
	$(CC) $(CFLAGS) $(SRC_DIRS)/main.c -o main

.PHONY: clean
clean:
	rm -f main