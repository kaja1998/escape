#include <stdio.h>
#include <stdlib.h>
#include "../include/game.h"
#include "../include/map.h"
#include "../include/constants.h"

/* Function to simulate water flooding across the map */
int floodWater(Map *map) {
    int i, j;
    int gameStatus = CONTINUE;
    char **mapGridCopy = (char**) malloc(sizeof(char*) * map->rows);

    /* "We make a copy of the map grid so that only the cells that already have water (‘~’) can spread it. 
        Without this copy, the new water cells would start spreading right away, 
        and the water would fill everything at once instead of spreading step by step as the player moves */
    for (i = 0; i < map->rows; i++) {
        mapGridCopy[i] = malloc(sizeof(char) * map->cols);
        for (j = 0; j < map->cols; j++)
            mapGridCopy[i][j] = map->mapGrid[i][j];  /* copy map */
    }

    for (i = 0; i < map->rows; i++) {
        for (j = 0; j < map->cols; j++) {
            if (map->mapGrid[i][j] == '~') { /* If the current cell is water, check cells next to it */


                /* Check if the cell above exists within the grid and is empty or player */
                if (i - 1 >= 0) {
                    if (mapGridCopy[i - 1][j] == ' ') {
                        mapGridCopy[i - 1][j] = '~'; /* water flows */
                    } else if (mapGridCopy[i - 1][j] == 'P') {
                        gameStatus = LOST;  /* player loses */
                        mapGridCopy[i - 1][j] = '~';
                    }
                }

                /* Check if the cell below exists within the grid and is empty or player */
                if (i + 1 < map->rows) {
                    if (mapGridCopy[i + 1][j] == ' ') {
                        mapGridCopy[i + 1][j] = '~';    /* water flows */
                    } else if (mapGridCopy[i][j + 1] == 'P'){
                        gameStatus = LOST;  /* player loses */
                        mapGridCopy[i + 1][j] = '~';
                    }
                }

                /* Check if the cell to the left exists within the grid and is empty or player */
                if (j - 1 >= 0) {
                    if (mapGridCopy[i][j - 1] == ' ') {
                        mapGridCopy[i][j - 1] = '~';  /* water flows */
                    } else if (mapGridCopy[i][j - 1] == 'P') {
                        gameStatus = LOST;  /* player loses */
                        mapGridCopy[i - 1][j] = '~';
                    }
                }

                /* Check if the cell to the right exists within the grid and is empty or player */
                if (j + 1 < map->cols) {
                    if (mapGridCopy[i][j + 1] == ' ') {
                        mapGridCopy[i][j + 1] = '~';  /* water flows */
                    } else if (mapGridCopy[i][j + 1] == 'P') {
                        gameStatus = LOST;  /* player loses */
                        mapGridCopy[i + 1][j] = '~'; 
                    }
                }
            }
        }
    }

    /* After processing, copy the modified mapGridCopy with the new water cells back to the original mapGrid */
    for (i = 0; i < map->rows; i++) {
        for (j = 0; j < map->cols; j++) {
            map->mapGrid[i][j] = mapGridCopy[i][j];
        }
        free(mapGridCopy[i]); /* Free the memory for each row in mapGridCopy */
    }
    free(mapGridCopy); /* Free the memory for the mapGridCopy array */

    return gameStatus;

}
