#ifndef MOVEMENT_H
#define MOVEMENT_H

void movePlayer(Map *map, int *playerPosX, int *playerPosY, char direction);
void updateMap(Map *map, int oldPlayerPosX, int oldPlayerPosY, int newplayerPosX, int newplayerPosY);
void updatePlayerPosition(int *playerPosX, int *playerPosY, int newplayerPosX, int newplayerPosY);

#endif
