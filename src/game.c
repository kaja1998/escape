#include <stdio.h>
#include "../include/game.h"
#include "../include/map.h"
#include "../include/input.h"
#include "../include/movement.h"
#include "../include/constants.h"


void gameLoop(Game *game) {
    int result = SUCCESS;
    char input;

    enableRawMode();

    /* Start game-loop */
    while (result == SUCCESS) {
        printMap(&game->map);
        printf("Enter move (w/a/s/d to move, q to quit): ");
        input = getInput();

        switch (input) {
            case 'w':  /* up */
            case 'a':  /* left */
            case 's':  /* down */
            case 'd':  /* right */
                movePlayer(&game->map, game->player.PlayerPosX, game->player.playerPosY, input);
                triggerTrap(&game->map);
                floodWater(&game->map);
                break;

            case 'u': /* undo */
                printf("Undoing last move.\n");
                undoLastMove(&game->map);
                continue;

            case 'q': /* Quit */
                printf("Exiting game.\n");
                result = FAILURE;
                break;

            default: /* invalid input */
                printf("Invalid input. Please try again.\n");
                continue;
        }

        if (checkForWin(&game->map)) { 
            printf("Congratulations, You Win!\n");
            break;
        }
        if (checkForLoss(&game->map)) {
            printf("Sorry, You Lost!\n");
            break;
        }
    }
    disableRawMode();
}