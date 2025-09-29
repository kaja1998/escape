#include <stdio.h>
#include <stdlib.h>
#include "../include/game.h"
#include "../include/map.h"
#include "../include/constants.h"


void movePlayer(Map *map, int playerPosX, int playerPosY, char direction) {
    int newplayerPosX = playerPosX;
    int newplayerPosY = playerPosY;
    char targetCell;

    /* Berechne neue Position basierend auf der Richtung */
    switch (direction) {
        case 'w':  /* nach oben */
            newplayerPosX--;
            break;
        case 'a':  /* nach links */
            newplayerPosY--;
            break;
        case 's':  /* nach unten */
            newplayerPosX++;
            break;
        case 'd':  /* nach rechts */
            newplayerPosY++;
            break;
    }

    /* Prüfe, ob das neue Feld innerhalb der Karten-Größen liegt */
    if (newplayerPosX >= 0 && newplayerPosX < map->rows && newplayerPosY >= 0 && newplayerPosY < map->cols) {
        /* Jetzt prüfen, ob das Ziel-Feld frei ist */
        targetCell = map->mapGrid[newplayerPosX][newplayerPosY];
        if (targetCell == ' ' || targetCell == 'W' || targetCell == 'T') {
            /* Ziel ist frei, also bewege den Spieler */
            printf("Player moves to (%d, %d)\n", newplayerPosX, newplayerPosY);
            map->mapGrid[playerPosX][playerPosY] = ' '; 
            map->mapGrid[newplayerPosX][newplayerPosY] = 'P';
        } else {
            printf("Cannot move there. It's blocked by %c\n", targetCell);
        }
    } else {
        printf("Move out of bounds!\n");
    }
}