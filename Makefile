CC = gcc
CFLAGS = -Wall -Iinclude

SRC_DIRS := ./src
INC_DIRS := ./include

SRCS := $(SRC_DIRS)/main.c $(SRC_DIRS)/queue.c
OBJS := $(SRCS:.c=.o)

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main

$(SRC_DIRS)/%.o: $(SRC_DIRS)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(SRC_DIRS)/*.o main
