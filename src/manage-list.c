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
    newNode->game = malloc(sizeof(Game));
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

    temp->prev->next = NULL;
    free(temp);
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

    /* Deep copy each row */
    for (i = 0; i < original->map.rows; i++) {
        newGame->map.mapGrid[i] = malloc(original->map.cols + 1);
        if (!newGame->map.mapGrid[i]) {
            perror("Failed to allocate memory for map row");
            exit(EXIT_FAILURE);
        }
        strcpy(newGame->map.mapGrid[i], original->map.mapGrid[i]);
    }

    return newGame;
}
