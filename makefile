CC = gcc
CFLAGS = -Wall -std=c89 -pedantic -g -Iinclude
TARGET = escape
SRCS = src/main.c src/map.c src/game.c src/movement.c src/water.c src/input.c src/manage-list.c
OBJS = src/main.o src/map.o src/game.o src/movement.o src/water.o src/input.o src/manage-list.o

all: $(TARGET)

# Link object files
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# .c files to .o files
main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

map.o: src/map.c include/map.h
	$(CC) $(CFLAGS) -c src/map.c -o src/map.o

game.o: src/game.c include/game.h
	$(CC) $(CFLAGS) -c src/game.c -o src/game.o

movement.o: src/movement.c include/movement.h
	$(CC) $(CFLAGS) -c src/movement.c -o src/movement.o

water.o: src/water.c include/water.h
	$(CC) $(CFLAGS) -c src/water.c -o src/water.o

input.o: src/input.c include/input.h
	$(CC) $(CFLAGS) -c src/input.c -o src/input.o

manage-list.o: src/manage-list.c include/manage_list.h include/node.h
	$(CC) $(CFLAGS) -c src/manage-list.c src/manage-list.o

clean:
	rm -f $(OBJS) $(TARGET)