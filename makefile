CC = gcc
CFLAGS = -Wall -std=c89 -pedantic -g -Iinclude
TARGET = escape
SRCS = src/main.c src/map.c src/game.c src/movement.c
OBJS = src/main.o src/map.o src/game.o src/movement.o

all: $(TARGET)

# Link object files
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# .c files to .o files
main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

map.o: src/map.c src/map.h
	$(CC) $(CFLAGS) -c src/map.c -o src/map.o

game.o: src/game.c src/game.h
	$(CC) $(CFLAGS) -c src/game.c -o src/game.o

movement.o: src/movement.c src/movement.h
	$(CC) $(CFLAGS) -c src/movement.c -o src/movement.o

clean:
	rm -f $(OBJS) $(TARGET)