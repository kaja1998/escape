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
    int gameStatus = CONTINUE;
    Node* head = NULL;
    Game* newGameCopy = NULL;
    game->map.trapTriggered = 0;

    insertAtEnd(&head, copyGame(game)); /* Put initial game state into list before start copying the game - initial game state remains clean */
    enableRawMode();    /* characters entered are send immediately to the program */

    /* Start game-loop */
    while (loopRuns == TRUE) {
        Node *currentStatus = getAtEnd(head);   /* Makes sure the status of the game is the last one in list */

        if (currentStatus == NULL) {    /* Should never happen, if so then initial state got deleted! */
            break;
        }

        clearScreen();
        printMap(&currentStatus->game->map);    /* print last game status in list */
        printf("Enter move (w/a/s/d to move, u to undo, q to quit): \n");
        input = getInput();

        switch (input) {
            case 'w':  /* up */
            case 'a':  /* left */
            case 's':  /* down */
            case 'd':  /* right */
                newGameCopy = copyGame(currentStatus->game); /* new game copy for next move */
                gameStatus = movePlayer(&newGameCopy->map,  /* Attempt to move the player and update the game status */
                        &newGameCopy->player.playerPosX,
                        &newGameCopy->player.playerPosY,
                        input);
                if (gameStatus == WON) {    /* Player reached the goal. Show final map, free all allocated memory and exit the game loop */
                    clearScreen();
                    printMap(&newGameCopy->map);
                    printf("You reached the goal! You win!\n");
                    loopRuns = FALSE;
                    freeGameCopy(newGameCopy);
                    freeLinkedList(&head); 
                } else if (gameStatus == LOST) {    /* Player lost the game. Show final map, free all allocated memory and exit the game loop */
                    clearScreen();
                    printMap(&newGameCopy->map);
                    printf("Player drowned in water! Game Over.\n");
                    freeGameCopy(newGameCopy);
                    freeLinkedList(&head);
                    loopRuns = FALSE;
                } else if (gameStatus == NO_MOVE) {
                    freeGameCopy(newGameCopy);
                } else {
                    insertAtEnd(&head, newGameCopy);    /* Successful move. Save new game state in the linked list */
                    newGameCopy = NULL;
                }
                break;
            case 'u':   /* Undo the last move */
                deleteAtEnd(&head);
                break;
            case 'q':   /* Quit the game */
                printf("Exiting game.\n");
                if (newGameCopy != NULL){
                    freeGameCopy(newGameCopy);
                }
                freeLinkedList(&head);
                loopRuns = FALSE;
                break;
            default:
                break;
        }
    }
    disableRawMode();   /* Restore terminal settings before exiting */
}

/* Clears the terminal screen */
/* Got that methode from: https://www.quora.com/How-do-you-clear-the-screen-in-C-programming */
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
