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

        /* Should never happen, if so then initial state got deleted! */
        if (currentStatus == NULL) {
            printf("No more moves to undo.\n");
            break;
        }

        printMap(&currentStatus->game->map);    /* print last game status in list */
        printf("Enter move (w/a/s/d to move, u to undo, q to quit): \n");
        input = getInput();
        printf("%c\n", input);

        switch (input) {
            case 'w':  /* up */
            case 'a':  /* left */
            case 's':  /* down */
            case 'd':  /* right */
                newGameCopy = copyGame(currentStatus->game); /* new game copy for next move */
                gameStatus = movePlayer(&newGameCopy->map,
                        &newGameCopy->player.playerPosX,
                        &newGameCopy->player.playerPosY,
                        input);
                if (gameStatus == WON) {
                    printMap(&newGameCopy->map);
                    printf("You reached the goal! You win!\n");
                    loopRuns = FALSE;
                    freeGameCopy(newGameCopy);
                    freeLinkedList(&head);
                } else if (gameStatus == LOST) {
                    printMap(&newGameCopy->map);
                    printf("Player stepped into water! Game Over.\n");
                    freeGameCopy(newGameCopy);
                    freeLinkedList(&head);
                    loopRuns = FALSE;
                } else if (gameStatus == NO_MOVE) {
                    printf("No move made.\n");
                    freeGameCopy(newGameCopy);
                } else {
                    insertAtEnd(&head, newGameCopy);
                    newGameCopy = NULL;
                }
                break;
            case 'u': /* undo */
                printf("Undoing last move.\n");
                deleteAtEnd(&head);
                break;
            case 'q': /* Quit */
                printf("Exiting game.\n");
                if (newGameCopy != NULL){
                    freeGameCopy(newGameCopy);
                }
                freeLinkedList(&head);
                loopRuns = FALSE;
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