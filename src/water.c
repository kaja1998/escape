#include <stdio.h>
#include <stdlib.h>
#include "../include/game.h"
#include "../include/map.h"
#include "../include/constants.h"


void floodWater(Map *map) {
    int i, j;
    char **mapGridCopy = malloc(sizeof(char*) * map->rows);

    for (i = 0; i < map->rows; i++) {
        mapGridCopy[i] = malloc(sizeof(char) * map->cols);
        for (j = 0; j < map->cols; j++)
            mapGridCopy[i][j] = map->mapGrid[i][j];  /* copy map */
    }

    for (i = 0; i < map->rows; i++) {
        for (j = 0; j < map->cols; j++) {
            if (map->mapGrid[i][j] == '~') {


                /* Check if the cell above exists within the grid and is empty */
                if (i - 1 >= 0 && mapGridCopy[i - 1][j] == ' ') {
                    mapGridCopy[i - 1][j] = '~'; /* water flows */
                }

                /* Check if the cell below exists within the grid and is empty */
                if (i + 1 < map->rows && mapGridCopy[i + 1][j] == ' ') {
                    mapGridCopy[i + 1][j] = '~'; /* water flows */
                }

                /* Check if the cell to the left exists within the grid and is empty*/
                if (j - 1 >= 0 && mapGridCopy[i][j - 1] == ' ') {
                    mapGridCopy[i][j - 1] = '~';  /* water flows */
                }

                /* Check if the cell to the right exists within the grid and is empty*/
                if (j + 1 < map->cols && mapGridCopy[i][j + 1] == ' ') {
                    mapGridCopy[i][j + 1] = '~';  /* water flows */
                }
            }
        }
    }


    /* neue Karte übernehmen */
    for (i = 0; i < map->rows; i++) {
        for (j = 0; j < map->cols; j++) {
            map->mapGrid[i][j] = mapGridCopy[i][j];
        }
        free(mapGridCopy[i]);
    }
    free(mapGridCopy);
}
