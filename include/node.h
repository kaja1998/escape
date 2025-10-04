#include "map.h"
#include "game.h"

#ifndef NODE_H
#define NODE_H

typedef struct Node {
    struct Player *player;
    struct Map *map;
    struct Node *next;
    struct Node *prev;
}Node;

#endif
