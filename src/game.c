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
        clearScreen();
        printMap(&game->map);
        printf("Enter move (w/a/s/d to move, u to undo, q to quit): \n");
        input = getInput();
        printf("%c\n", input);

        switch (input) {
            case 'w':  /* up */
            case 'a':  /* left */
            case 's':  /* down */
            case 'd':  /* right */
                printf("PlayerPosition: %d %d \n", game->player.PlayerPosX, game->player.playerPosY);
                movePlayer(&game->map, &game->player.PlayerPosX, &game->player.playerPosY, input);
                break;

            case 'u': /* undo */
                printf("Undoing last move.\n");
                continue;

            case 'q': /* Quit */
                printf("Exiting game.\n");
                result = FAILURE;
                break;

            default: /* invalid input */
                printf("Invalid input. Please try again.\n");
                continue;
        }
    }
    disableRawMode();
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}