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
    int isNewList = 0;
    Node *newNode = createNode(game);
    Node *temp;

    /* Empty list */
    if (*head == NULL) {
        isNewList = 1;
        *head = newNode;  
    }

    /* Pre-existing list */
    if(isNewList == 0) {
        temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }

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

    temp = *head;

    /* If only one node, keep it (optional) */
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

Node* getAtEnd(Node* head) {
    Node* temp = head;

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
