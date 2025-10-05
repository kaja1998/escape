#ifndef MANAGE-LIST_H
#define MANAGE-LIST_H

#include "player.h"
#include "map.h"
#include "node.h"

Node* createNode(Game *game);
void insertAtEnd(Node **head, Game *game);
void deleteAtEnd(Node** head);
Node* getAtEnd(Node* head);
Game* copyGame(Game* original);

#endif
