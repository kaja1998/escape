#include <stdio.h>
#include <stdlib.h>
#include "../include/game.h"
#include "../include/input.h"
#include "../include/movement.h"
#include "../include/constants.h"
#include "../include/node.h"
#include "../include/manage_list.h"


void gameLoop(Game *game) {
    int loopRuns = TRUE;
    char input;
    Node* head = NULL;
    int gameStatus = CONTINUE;
    game->map.trapTriggered = 0;

    insertAtEnd(&head, copyGame(game)); /* Put initial game state into list */
    enableRawMode();    /* characters entered are send immediately to the program */

    /* Start game-loop */
    while (loopRuns == TRUE) {
        Node *currentStatus = getAtEnd(head);   /* Makes sure the status of the game is the latest */

        /* Should never happen, if so then initial state got deleted! */
        if (currentStatus == NULL) {
            printf("No more moves to undo.\n");
            break;
        }

        printMap(&currentStatus->game->map);
        printf("Enter move (w/a/s/d to move, u to undo, q to quit): \n");
        input = getInput();
        printf("%c\n", input);

        switch (input) {
            case 'w':  /* up */
            case 'a':  /* left */
            case 's':  /* down */
            case 'd':  /* right */
                gameStatus = movePlayer(&currentStatus->game->map,
                        &currentStatus->game->player.playerPosX,
                        &currentStatus->game->player.playerPosY,
                        input);
                if (gameStatus == WON) {
                    printMap(&currentStatus->game->map);
                    printf("You reached the goal! You win!\n");
                    loopRuns = FALSE;
                } else if (gameStatus == LOST) {
                    printMap(&currentStatus->game->map);
                    printf("Player stepped into water! Game Over.\n");
                    loopRuns = FALSE;
                } else {
                    insertAtEnd(&head, copyGame(currentStatus->game));
                }
                break;
            case 'u': /* undo */
                printf("Undoing last move.\n");
                deleteAtEnd(&head);
                break;
            case 'q': /* Quit */
                printf("Exiting game.\n");
                loopRuns = FALSE;
                break;
            default:
                printf("Invalid input. Please try again.\n");
                continue;
        }
    }

    /* !!!!!!!!!!!!! free copygame memory */  
    disableRawMode();
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}