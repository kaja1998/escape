#include <stdio.h>
#include <stdlib.h>
#include "../include/game.h"
#include "../include/map.h"
#include "../include/constants.h"

int main(int argc, char *argv[]) {
    int mapLoad = FAILURE;
    Game *game = malloc(sizeof(Game));  /* Allocate memory for the Game structure */
    game->map.mapGrid = NULL; /* Set to NULL so destroyMap can safely free on load failure */

    /* Was exactly one argument provided? */
    if (argc != 2) {
        printf("Not Accepted. You have to use './escape maps/map.txt'.\n");
        mapLoad = FAILURE;
    } else {
        mapLoad = loadMap(game, argv[1]); /* if yes, then loadMap */
    }
    
    if (mapLoad == SUCCESS) {
        gameLoop(game); /* Map successfully loaded. Start game */
    } else {
        printf("Error: Map could not be loaded.\n");
    }
    
    destroyMap(&game->map); /* Free map memory after gameLoop or failure of mapLoad */
    free(game); /* Free game struc */

    return mapLoad; 
}
