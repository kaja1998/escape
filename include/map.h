#ifndef MAP_H
#define MAP_H

char numToSymbol(int num);
int allocateMap(Map *map, int rows, int cols);
int loadMap(Game *game, const char *filename);
void printMap(Map *map);
void destroyMap(Map *map);

#endif