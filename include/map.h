#ifndef MAP_H
#define MAP_H

struct Game;

typedef struct Map {
    int rows;
    int cols;
    char **mapGrid;
} Map;

char numToSymbol(int num);
int allocateMap(Map *map, int rows, int cols);
int loadMap(struct Game *game, const char *filename);
void printMap(Map *map);
void destroyMap(Map *map);

#endif
