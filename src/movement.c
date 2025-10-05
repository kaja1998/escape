#include <stdio.h>
#include <stdlib.h>
#include "../include/game.h"
#include "../include/map.h"
#include "../include/constants.h"

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

void movePlayer(Map *map, int *playerPosX, int *playerPosY, char direction) {
    int newplayerPosX = *playerPosX;
    int newplayerPosY = *playerPosY;
    int trapTriggered = 0;
    char targetPos;

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

        if (targetPos == ' ' || targetPos == '~' || targetPos == 'G' || targetPos == '@') {

            if (targetPos == '@') {
                trapTriggered = 1;  /* set trap triggered to true */
                removeTraps(map);
            }
            /* target position is free, move player */
            printf("Player moves to (%d, %d)\n", newplayerPosX, newplayerPosY);
            printf("Old Player pos is now ' '(%d, %d)\n", *playerPosX, *playerPosY);
            updateMap(map, *playerPosX, *playerPosY, newplayerPosX, newplayerPosY);     /* pass variable */
            updatePlayerPosition(playerPosX, playerPosY, newplayerPosX, newplayerPosY);     /* pass pointer */

            if (trapTriggered) {
                floodWater(map);
            }
        } else {
            printf("Cannot move there. It's blocked by %c\n", targetPos);
        }
    } else {
        printf("Move out of bounds!\n");
    }
}
