#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/node.h"

/* Function to create a new node with given value as data */
Node* createNode(Game *gameCopy) {
    Node* newNode = NULL;
    newNode = (Node*)malloc(sizeof(Node));

    /* Check if allocation has been successful before proceeding */
    if (newNode != NULL) {
        newNode->game = gameCopy;   /* Allocate and copy Player */

        /* Check if gameCopy that was passed to the method is != NULL */
        if (newNode->game != NULL) {

            *(newNode->game) = *gameCopy;   /* Copy the contents of the provided Game into the new one */
            newNode->next = NULL;
            newNode->prev = NULL;
        } else {
            newNode = NULL;
            free(newNode);
        }
    }
    return newNode;
}

/* Function to insert a node at the end */
void insertAtEnd(Node **head, Game *game) {
    int isNewList = 0;      /* local var to remeber if list was empty (new) or already existing */
    Node *newNode = createNode(game);      /* Create a new node using the provided game data */
    Node *temp;

    /* Check if the list is empty */
    if(newNode != NULL) {
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
    }
}

/* Function finds and returns the last node of the linked list. 
    If the list is empty (head == NULL), it returns NULL. */
Node* getAtEnd(Node* head) {
    Node* temp = head;      /* Gets pointer to the head of the linked list */

    /* Move to the end of the list */
    while (temp != NULL && temp->next != NULL) {
        temp = temp->next;
    }

    return temp;
}

/* Create a deep copy of game */
Game* copyGame(const Game* original) {
    int i, j;

    /* Check if memory could be allocated */
    Game* newGame = (Game*) malloc(sizeof(Game));
    if (newGame != NULL) {
        /* Copy simple fields */
        newGame->player = original->player;
        newGame->map.rows = original->map.rows;
        newGame->map.cols = original->map.cols;
        newGame->map.trapTriggered = original->map.trapTriggered;

        /* Allocate mapGrid (array of row pointers) */
        newGame->map.mapGrid = malloc(original->map.rows * sizeof(char*));
        if (newGame->map.mapGrid != NULL) {
            /* Allocate and copy each row */
            for (i = 0; i < original->map.rows; i++) {
                newGame->map.mapGrid[i] = malloc(original->map.cols * sizeof(char));
                if (newGame->map.mapGrid[i] == NULL) {
                    printf("Error: Failed to allocate memory for map row %d\n", i);
                    /* Free any previously allocated rows */
                    for (j = 0; j < i; j++) {
                        free(newGame->map.mapGrid[j]);
                    }
                    free(newGame->map.mapGrid);
                    /* Free newGame and set NULL to prevent dangling pointer */
                    free(newGame);
                    newGame = NULL;
                } else {
                    for (j = 0; j < original->map.cols; j++) {
                        newGame->map.mapGrid[i][j] = original->map.mapGrid[i][j];
                    }
                }
            }
        } else {
            printf("Error: Failed to allocate memory for mapGrid\n");
            free(newGame);
        }
    } else {
        printf("Error: Failed to allocate memory for Game\n");
    }

    return newGame;
}

/* Frees game copy that was not added to the list */
void freeGameCopy(Game *gameCopy){
    int i;
    /* Free the 2D map grid */
    if (gameCopy->map.mapGrid != NULL) {
        for (i = 0; i < gameCopy->map.rows; i++) {
            free(gameCopy->map.mapGrid[i]);  /* Free each row */
        }
        free(gameCopy->map.mapGrid);  /* Free the array of row pointers */
        gameCopy->map.mapGrid = NULL;
    }

    /* Free the game struct itself */
    free(gameCopy);
}

/* Frees the whole linked list after won or lose */
void freeLinkedList(Node **head) {
    Node *currentGame = *head;
    Node *next;

    /* Keep going until end of list */
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
    /* Check if list is empty */
    if (*head != NULL) {
        temp = *head;   /* Points to the first node */

        if (temp->next != NULL) {   /* If only one node, refuses to delete because this is initial game */
            while (temp->next != NULL) {    /* Traverse to the last node */
                temp = temp->next;
            }

            freeGameCopy(temp->game);
            temp->prev->next = NULL; /* Disconnects the last node from list */
            free(temp); /*free note */
        } else {
            return; /* Cannot undo the initial state */
        }
    } else {
        printf("The list is already empty.\n");
    }
}
