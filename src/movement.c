#include <stdio.h>
#include <stdlib.h>
#include "../include/game.h"
#include "../include/map.h"
#include "../include/constants.h"
#include "../include/water.h"

void updateMap(Map *map, int oldPlayerPosX, int oldPlayerPosY, int newplayerPosX, int newplayerPosY) {
    map->mapGrid[oldPlayerPosX][oldPlayerPosY] = ' ';
    map->mapGrid[newplayerPosX][newplayerPosY] = 'P'; 
}

void updatePlayerPosition(int *playerPosX, int *playerPosY, int newplayerPosX, int newplayerPosY) {
    *playerPosX = newplayerPosX;
    *playerPosY = newplayerPosY;
}

void removeTraps(Map *map) {
    int i;
    int j;
    for (i = 0; i < map->rows; i++) {
        for (j = 0; j < map->cols; j++) {
            if (map->mapGrid[i][j] == 'X') {
                map->mapGrid[i][j] = ' '; 
            }
        }
    }
}

int movePlayer(Map *map, int *playerPosX, int *playerPosY, char direction) {
    int newplayerPosX = *playerPosX;
    int newplayerPosY = *playerPosY;
    char targetPos;
    int gameStatus = CONTINUE;

    /* Calulate new Player position based on direction */
    switch (direction) {
        case 'w':  /* up */
            newplayerPosX--;
            break;
        case 'a':  /* left */
            newplayerPosY--;
            break;
        case 's':  /* down */
            newplayerPosX++;
            break;
        case 'd':  /* right */
            newplayerPosY++;
            break;
    }

    /* check if new Position is a pos on map */
    if (newplayerPosX >= 0 && newplayerPosX < map->rows && newplayerPosY >= 0 && newplayerPosY < map->cols) {
        /* target-position free? */
        targetPos = map->mapGrid[newplayerPosX][newplayerPosY];

        if (targetPos == '~') {
            gameStatus = LOST;
        } else if (targetPos == 'G') {  /* player steps on goal and wins */
            updateMap(map, *playerPosX, *playerPosY, newplayerPosX, newplayerPosY);
            updatePlayerPosition(playerPosX, playerPosY, newplayerPosX, newplayerPosY);
            gameStatus = WON;
        } else if (targetPos == ' ' || targetPos == '@') {
            if (targetPos == '@') {     /* players steps on trap */
                map->trapTriggered = 1; /* Set var to true*/
                removeTraps(map);       /* remove traps so water starts to spread */
            }

            updateMap(map, *playerPosX, *playerPosY, newplayerPosX, newplayerPosY);
            updatePlayerPosition(playerPosX, playerPosY, newplayerPosX, newplayerPosY);

            if (map->trapTriggered) {   /* Check if var is true */
                gameStatus = floodWater(map);    /* if true, water starts to spread */
            }
        } else {
            gameStatus = NO_MOVE; /* Can not move there. It's blocked by wall (0) or Traps (X)*/
        }
    } else {
        gameStatus = NO_MOVE;   /* Move out of bounds (*). Do nothing. */
    }
    return gameStatus;
}
