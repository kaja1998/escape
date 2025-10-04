#ifndef MANAGE-LIST_H
#define MANAGE-LIST_H

#include "player.h"
#include "map.h"
#include "node.h"

Node* createNode(Player *player, Map *map);
void insertAtBeginning(Node** head, Player *player, Map *map);
void insertAtEnd(Node** head, Player *player, Map *map);
void insertAtPosition(Node** head, Player *player, Map *map, int position);
void deleteAtBeginning(Node** head);
void deleteAtEnd(Node** head);
void deleteAtPosition(Node** head, int position);
Node* getAtEnd(Node* head);
void printListForward(Node* head);
void printListReverse(Node* head);

#endif
