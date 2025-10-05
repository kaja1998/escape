#include <stdio.h>
#include <stdlib.h>
#include "../include/game.h"
#include "../include/map.h"
#include "../include/constants.h"

#include <stdio.h>
#include <stdlib.h>
#include "../include/game.h"
#include "../include/map.h"
#include "../include/constants.h"


int main(int argc, char *argv[]) {
    int mapResult = FAILURE;
    Game *game = malloc(sizeof(Game));  /* Allocate memory for the Game structure */

    /* First check: was exactly one argument provided? */
    if (argc != 2) {
        printf("Not Accepted. You used: ./escape <map_file>\n");
        mapResult = FAILURE;
    } 
    
    mapResult = loadMap(&game->map, argv[1]);
    
    if (mapResult == FAILURE) {
        printf("Error loading map file.\n");  
        destroyMap(&game->map); /* Pointer on map member */
        free(game);
    } else {
        gameLoop(game);  /* Map successfully loaded. Start game */
    }

    printf("res = %d\n", mapResult);

    return mapResult; 
}