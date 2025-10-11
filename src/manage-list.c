#include "../include/node.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Function to create a new node with given value as data */
Node* createNode(Game *game) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    /* Allocate and copy Player */
    newNode->game = game;
    if (!newNode->game) {
        fprintf(stderr, "Memory allocation failed for game\n");
        exit(EXIT_FAILURE);
    }
    *(newNode->game) = *game;  /* copy struct contents */

    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

/* Function to insert a node at the end */
void insertAtEnd(Node **head, Game *game) {
    int isNewList = 0; /* local var to remeber if list was empty (new) or already existing */
    Node *newNode = createNode(game); /* Create a new node using the provided game data */
    Node *temp;

    /* Check if the list is empty */
    if (*head == NULL) {
        isNewList = 1;
        *head = newNode;  /* If empty, set the new node as the head of the list */
    }

    /* If the list already has nodes */
    if(isNewList == 0) {
        temp = *head;

        /* Traverse to the last node */
        while (temp->next != NULL) {
            temp = temp->next;
        }

        /* Link the new node at the end of the list */
        temp->next = newNode;
        newNode->prev = temp;
    }

    if (*head != NULL) {
        printf("Game player position %d %d\n",
            game->player.playerPosX,
            game->player.playerPosY);
        printf("Head player position %d %d\n",
            (*head)->game->player.playerPosX,
            (*head)->game->player.playerPosY);
    }
}

/* Function finds and returns the last node of the linked list. 
    If the list is empty (head == NULL), it returns NULL. 
*/
Node* getAtEnd(Node* head) {
    Node* temp = head;      /* gets pointer to the head of the chained list */

    /* Move to the end of the list */
    while (temp != NULL && temp->next != NULL) {
        temp = temp->next;
    }

    return temp;
}

Game* copyGame(Game* original) {
    int i;
    int j;
    Game* newGame = malloc(sizeof(Game));
    if (!newGame) {
        perror("Failed to allocate memory for game copy");
        exit(EXIT_FAILURE);
    }

    /* Copy the player */
    newGame->player = original->player;

    /* Copy map dimensions */
    newGame->map.rows = original->map.rows;
    newGame->map.cols = original->map.cols;
    newGame->map.trapTriggered = original->map.trapTriggered;

    /* Allocate memory for the new map grid */
    newGame->map.mapGrid = malloc(original->map.rows * sizeof(char*));
    if (!newGame->map.mapGrid) {
        perror("Failed to allocate memory for mapGrid");
        exit(EXIT_FAILURE);
    }

    /* Deep copy each row and col like in map.c */
    for (i = 0; i < original->map.rows; i++) {
        newGame->map.mapGrid[i] = malloc(original->map.cols * sizeof(char));
        if (!newGame->map.mapGrid[i]) {
            perror("Failed to allocate memory for map row");
            exit(EXIT_FAILURE);
        }
        for (j = 0; j < original->map.cols; j++) {
            newGame->map.mapGrid[i][j] = original->map.mapGrid[i][j];
        }
    }

    return newGame;
}

/* Frees game copy that was not added to the list */
void freeGameCopy(Game *game){
    int i;
    /* Free the 2D map grid */
    if (game->map.mapGrid != NULL) {
        for (i = 0; i < game->map.rows; i++) {
            free(game->map.mapGrid[i]);  /* Free each row */
        }
        free(game->map.mapGrid);  /* Free the array of row pointers */
        game->map.mapGrid = NULL;
    }

    /* Free the game struct itself */
    free(game);
}

/* Frees the whole linked list after won or lose */
void freeLinkedList(Node **head) {
    Node *currentGame = *head;
    Node *next;

    while (currentGame != NULL) {
        next = currentGame->next;

        if (currentGame->game != NULL)
            freeGameCopy(currentGame->game);  /* Frees game and its map */

        free(currentGame);  /* Free the node */
        currentGame = next;
    }

    *head = NULL;  /* Prev dangling pointer */
}


/* Function to delete a node from the end */
void deleteAtEnd(Node **head) {           
    Node* temp;
    if (*head == NULL) {
        printf("The list is already empty.\n");
        return;
    }

    temp = *head; /* Points to the first node */

    /* If only one node, refuses to delete because this is initial game */
    if (temp->next == NULL) {
        printf("Cannot undo the initial state.\n");
        return;
    }

    /* Traverse to the last node */
    while (temp->next != NULL) {
        temp = temp->next;
    }

    freeGameCopy(temp->game);
    temp->prev->next = NULL; /* Disconnects the last node from list */
    free(temp); /*free note */
}
