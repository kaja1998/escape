#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "map.h"

typedef struct Game {
    Map map;
    Player player; 
} Game;

void gameLoop(Game *game);
void clearScreen();

#endif
