#include <stdlib.h>
#include <stdio.h>

#include "engine.h"
#include "space.h"

#define ENGINE_ON 1
#define ENGINE_OFF -1

extern struct Engine ng;

void
engine_start()
{
    ng.status = ENGINE_ON;

    ng.window.width = 1280;
    ng.window.height = 720;
    render_setup(&ng.window);

    FILE *f = fopen("config.edn", "r");
    // read
    fclose(f);

    ng.scene.vertices[0][0] = -5;
    ng.scene.vertices[0][1] =  0;
    ng.scene.vertices[0][2] = -4;

    ng.scene.vertices[1][0] =  5;
    ng.scene.vertices[1][1] =  0;
    ng.scene.vertices[1][2] = -4;

    ng.scene.vertices[2][0] =  0;
    ng.scene.vertices[2][1] =  0;
    ng.scene.vertices[2][2] =  6;
}

void
engine_stop()
{
}

void
engine_off()
{
    ng.status = ENGINE_OFF;
}

void
space_init(struct Space *space)
{
    for (unsigned int ci = 0; ci < (SPACE_CELLS_SIZE / sizeof(int)); ci++)
    {
        space->cells_gc[ci] = 0;
    }
    space->cells_gci = 0;

    for (unsigned int oi = 0; oi < (SPACE_OBJECTS_SIZE / sizeof(int)); oi++)
    {
        space->objects_gc[oi] = 0;
    }
    space->objects_gci = 0;

    for (unsigned int si = 0; si < (SPACE_OBJECTS_SIZE / sizeof(int)); si++)
    {
        space->surfaces_gc[si] = 0;
    }
    space->surfaces_gci = 0;

    for (unsigned int fi = 0; fi < (SPACE_OBJECTS_SIZE / sizeof(int)); fi++)
    {
        space->cells_gc[fi] = 0;
    }
    space->faces_gci = 0;
}

int
main(void)
{
    struct Space space;

    space_init(&space);

    engine_start();

    while (ng.status == ENGINE_ON)
    {
        render_frame(&ng.window, &ng.scene, &engine_off);
    }

    engine_stop();

    return 0;
}

