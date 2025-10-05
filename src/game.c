#include <stdio.h>
#include <stdlib.h>
#include "../include/game.h"
#include "../include/input.h"
#include "../include/movement.h"
#include "../include/constants.h"
#include "../include/node.h"
#include "../include/manage-list.h"


void gameLoop(Game *game) {
    int result = SUCCESS;
    char input;
    Node* head = NULL;
    game->map.trapTriggered = 0;



    insertAtEnd(&head, copyGame(game)); 



    enableRawMode();

    /* Start game-loop */
    while (result == SUCCESS) {
        Node *currentStatus = getAtEnd(head);   /* Makes sure the status of the game is the latest */

        /* Should never happen, if so then initial state got deleted! */
        if (currentStatus == NULL) {
            printf("No more moves to undo.\n");
            break;  /* or continue; depending on desired behavior */
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
                movePlayer(&currentStatus->game->map,
                        &currentStatus->game->player.playerPosX,
                        &currentStatus->game->player.playerPosY,
                        input);

                insertAtEnd(&head, copyGame(currentStatus->game));
                break;
            case 'u': /* undo */
                printf("Undoing last move.\n");
                deleteAtEnd(&head);
                break;
            case 'q': /* Quit */
                printf("Exiting game.\n");
                result = FAILURE;
                break;
            default:
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