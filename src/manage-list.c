#include "../include/player.h"
#include "../include/node.h"
#include "../include/map.h"
#include <stdio.h>
#include <stdlib.h>

/* Function to create a new node with given value as data */
Node* createNode(Player *player, Map *map) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->player = player;
    newNode->map = map;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

/* Function to insert a node at the beginning */
void insertAtBeginning(Node** head, Player *player, Map *map) {
    /* creating new node */
    Node* newNode = createNode(player, map);

    /* check if DLL is empty */
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    newNode->next = *head;
    (*head)->prev = newNode;
    *head = newNode;
}

/* Function to insert a node at the end */
void insertAtEnd(Node** head, Player *player, Map *map) {
    /* creating new node */
    Node* newNode;
    Node* temp;
    
    newNode = createNode(player, map);

    /* check if DLL is empty */
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

/* Function to insert a node at a specified position */
void insertAtPosition(Node** head, Player *player, Map *map, int position) {
    Node* newNode;
    Node* temp;
    int i;
    
    if (position < 1) {
        printf("Position should be >= 1.\n");
        return;
    }

    /* if we are inserting at head */
    if (position == 1) {
        insertAtBeginning(head, player, map);
        return;
    }
    
    newNode = createNode(player, map);
    temp = *head;
    for (i = 1; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf(
            "Position greater than the number of nodes.\n");
        return;
    }
    
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
}

/* Function to delete a node from the beginning */
void deleteAtBeginning(Node** head) {
    Node* temp;
    
    /* checking if the DLL is empty */
    if (*head == NULL) {
        printf("The list is already empty.\n");
        return;
    }

    temp = *head;
    *head = (*head)->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    }

    free(temp);
}

/* Function to delete a node from the end */
void deleteAtEnd(Node** head) {
    Node* temp;
    
    /* checking if DLL is empty */
    if (*head == NULL) {
        printf("The list is already empty.\n");
        return;
    }

    temp = *head;
    if (temp->next == NULL) {
        *head = NULL;
        free(temp);
        return;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->prev->next = NULL;
    free(temp);
}

/* Function to delete a node from a specified position  */
void deleteAtPosition(Node** head, int position) {
    Node* temp;
    int i;
    
    if (*head == NULL) {
        printf("The list is already empty.\n");
        return;
    }

    temp = *head;
    if (position == 1) {
        deleteAtBeginning(head);
        return;
    }

    for (i = 1; temp != NULL && i < position; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Position is greater than the number of "
               "nodes.\n");
        return;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }

    free(temp);
}

/* Function to print the list in forward direction */
void printListForward(Node* head) {
    Node* temp = head;
    printf("Forward List");
    while (temp != NULL) {
        temp = temp->next;
    }
    printf("\n");
}

/* Function to print the list in reverse direction */
void printListReverse(Node* head) {
    Node* temp = head;
    if (temp == NULL) {
        printf("The list is empty.\n");
        return;
    }
    /* Move to the end of the list */
    while (temp->next != NULL) {
        temp = temp->next;
    }
    /* Traverse backwards */
    printf("Reverse List");
    while (temp != NULL) {
        temp = temp->prev;
    }
    printf("\n");
}
