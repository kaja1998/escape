#ifndef GAME_H
#define GAME_H

typedef struct {
    int rows;
    int cols;
    char **mapGrid;       /* 2D array of the map */
}Map;

typedef struct {
    int PlayerPosX;
    int playerPosY;
}Player;

typedef struct {
    Map map;
    Player player; 
    /*Water *waters;
    Trap *traps; */
} Game;

void gameLoop(Game *game);

#endif