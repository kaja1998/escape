#include <stdio.h>
#include <stdlib.h>
#include "../include/game.h"
#include "../include/map.h"
#include "../include/constants.h"

/* Allocates memory for a 2D character map with the given number of rows and columns */
int allocateMap(Map *map, int rows, int cols) {
    int i;
    map->rows = rows;       /* Storage size of the dimensions */
    map->cols = cols;

    map->mapGrid = malloc(rows * sizeof(char*));      /* Allocate memory space for the rows (array of char* pointers) */
    for (i = 0; i < rows; i++) {
        map->mapGrid[i] = malloc(cols * sizeof(char));        /* Allocate memory space for the columns in each row */
    }
    return SUCCESS;
}

/* Translates each number from the file into a symbol */
char numToSymbol(int num) {
    char symbol; 
    switch (num) {
        case 0: symbol = ' '; break;
        case 1: symbol = 'O'; break;
        case 2: symbol = '~'; break;
        case 3: symbol = 'X'; break;
        case 4: symbol = '@'; break;
        case 5: symbol = 'P'; break;
        case 6: symbol = 'G'; break;
        default: symbol = '?'; break;
    }
    return symbol;
}


/* Opens the file and loads the map */
int loadMap(Game *game, const char *filename) {
    int result = SUCCESS; /* false */
    int rows = 0;
    int cols = 0;    /* Declare rows and coloums */
    int i;
    int j;
    int fileValue;
    FILE *file = fopen(filename, "r");      /* Opens the file if possible */
   
    if (!file){     /* check if it is possible to open file */
        result = FAILURE;
        printf("fail 1: Could not open file.\n");
    } else if(fscanf(file, "%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0) {     /* Scan first row to see how big the memory has to be */
        fclose(file);
        result = FAILURE;
        printf("fail 2: Could not read two ints for rows and cols.\n");
    } else if(!allocateMap(&game->map, rows, cols)) {        /* Address of map to function. If map allocating fails, close file and return failure */
        fclose(file);
        result = FAILURE;
        printf("fail 3: Allocating map failed. res= %d\n", result);
    } else {
        for (i = 0; i < rows && result == SUCCESS ; i++) {
            for (j = 0; j < cols && result == SUCCESS ; j++) {
                if (fscanf(file, "%d", &fileValue) != 1) {      /* Tries to read one by one integer from the file */
                    result = FAILURE;     /* If the file format is incorrect (!=1) will return false */
                    printf("fail 4: Invalid map file format detected. res= %d\n", result);
                }
                game->map.mapGrid[i][j] = numToSymbol(fileValue);      /* If reading was successfull, the value will be transformed into a symbol and saved into 2d array cells*/
            
                if (game->map.mapGrid[i][j] == 'P') {       /* get player Position */
                    game->player.playerPosX = i;  
                    game->player.playerPosY = j; 
                }
            }
        }
        fclose(file);
    }
    return result;
}


/* Print map on display */
void printMap(Map *map) {
    int i;
    int j;

    for (j = 0; j < map->cols + 2; j++) {
        printf("*");
    }
    printf("\n");

    for (i = 0; i < map->rows; i++) {
        printf("*");
        for (j = 0; j < map->cols; j++) {
            char c = map->mapGrid[i][j];
            if (c == '@') {
                printf("\033[41m%c\033[0m", c);     /* Set Background to red, put c and reset after. Syntax: \033[<Code>m */
            }
            else if (c == 'G'){
                printf("\033[42m%c\033[0m", c);     /* Background green */
            }     else if (c == '~') {
            printf("\033[44m%c\033[0m", c); /* blue */
    }   else {
                printf("%c", c);        /* For all others without */
            }
        }
        printf("*");
        printf("\n");
    }

    for (j = 0; j < map->cols + 2; j++) {
        printf("*");
    }
    printf("\n");
}

/* Free memory of map */
void destroyMap(Map *map) {
    int i;
    if (map->mapGrid) {       /* Only free if memory was allocated */
        for (i = 0; i < map->rows; i++) {
            free(map->mapGrid[i]);        /* Free each row */
            map->mapGrid[i] = NULL;
        }
        free(map->mapGrid);
        map->mapGrid = NULL;
    }
}