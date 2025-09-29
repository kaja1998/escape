#ifndef TRAPDOORS_H
#define TRAPDOORS_H

typedef struct {
    int x;
    int y;
    int **trapdoorGrid;
} Trapdoors;

typedef struct {
    int x;  // x-Koordinate der Trapdoor (Zeile)
    int y;  // y-Koordinate der Trapdoor (Spalte)
} Trapdoor;

typedef struct {
    Trapdoor *trapdoors;  // Dynamisches Array der Trapdoors
    int trapCount;        // Anzahl der Trapdoors
} TrapdoorList;

#endif
