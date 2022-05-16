#ifndef SPACE_H
#define SPACE_H

#include "object.h"

#define SPACE_CELLS_SIZE    1024
#define SPACE_OBJECTS_SIZE  1024
#define SPACE_SURFACES_SIZE 1024
#define SPACE_FACES_SIZE    1024

struct Cell {
    int cells[8]; // 8 for chaining
    int objects[56];
};

struct Space {
    struct Cell cells[SPACE_CELLS_SIZE];
    int cells_gc[SPACE_CELLS_SIZE / sizeof(int)];
    int cells_gci;

    struct Object objects[SPACE_OBJECTS_SIZE];
    int objects_gc[SPACE_OBJECTS_SIZE / sizeof(int)];
    int objects_gci;

    struct Surface surfaces[SPACE_SURFACES_SIZE];
    int surfaces_gc[SPACE_SURFACES_SIZE / sizeof(int)];
    int surfaces_gci;

    struct Face faces[SPACE_FACES_SIZE];
    int faces_gc[SPACE_FACES_SIZE / sizeof(int)];
    int faces_gci;
};

#endif
