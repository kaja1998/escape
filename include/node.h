#include "game.h"

#ifndef NODE_H
#define NODE_H

typedef struct Node {
    struct Game *game;
    struct Node *next;
    struct Node *prev;
}Node;

#endif
