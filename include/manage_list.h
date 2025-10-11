#ifndef MANAGE_LIST_H
#define MANAGE_LIST_H

#include "player.h"
#include "map.h"
#include "node.h"

Node* createNode(Game *game);
void insertAtEnd(Node **head, Game *game);
void deleteAtEnd(Node** head);
Node* getAtEnd(Node* head);
Game* copyGame(Game* original);
void freeLinkedList(Node **head);
void freeGameCopy(Game *game);

#endif
