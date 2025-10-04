#include <stdio.h>
#include <stdlib.h>
#include "../include/game.h"
#include "../include/input.h"
#include "../include/movement.h"
#include "../include/constants.h"
#include "../include/node.h"
#include "../include/manage-list.h"


void gameLoop(Game *game) {
    Node* head = NULL;
    int result = SUCCESS;
    char input;

    insertAtEnd(&head, &game->player, &game->map); 

    enableRawMode();

    /* Start game-loop */
    while (result == SUCCESS) {
        Node* currentStatus = getAtEnd(head);

        if (currentStatus == NULL) {
            printf("No more moves to undo.\n");
            break;  // or continue; depending on desired behavior
        }

        printMap(currentStatus->map);
        printf("Enter move (w/a/s/d to move, u to undo, q to quit): \n");
        input = getInput();
        printf("%c\n", input);

        switch (input) {
            case 'w':  /* up */
            case 'a':  /* left */
            case 's':  /* down */
            case 'd':  /* right */
                movePlayer(&game->map, &game->player.playerPosX, &game->player.playerPosY, input);
                insertAtEnd(&head, &game->player, &game->map);
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