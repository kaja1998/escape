#ifndef MOVEMENT_H
#define MOVEMENT_H

void movePlayer(Map *map, int *playerPosX, int *playerPosY, char direction);
void updateMap(Map *map, int oldPosX, int oldPosY, int newPosX, int newPosY);

#endif
