#include <stdio.h>
#include <stdlib.h>
#include "../include/game.h"
#include "../include/map.h"
#include "../include/constants.h"


int main(int argc, char *argv[]) {
    int result = FAILURE;
    Game *game = malloc(sizeof(Game));  /* Allocate memory for the Game structure */

    /* First check: was exactly one argument provided? */
    if (argc != 2) {
        printf("Not Accepted. You used: ./escape <map_file>\n");
        result = FAILURE;  
    /* Second check: try to load the map */
    } else if (loadMap(&game->map, argv[1] == FAILURE)) {
        printf("Error loading map file.\n");
        result = FAILURE;
    }

    if (result == SUCCESS) {
        gameLoop(game);  /* Map successfully loaded. Start game */
    }

    destroyMap(&game->map); /* Pointer on map member */
    free(game);
    return result; 
}