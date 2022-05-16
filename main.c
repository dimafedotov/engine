#include <stdlib.h>
#include <stdio.h>

#include "render.h"

#define ENGINE_ON 1
#define ENGINE_OFF -1

struct Engine {
    struct RenderWindow window;
    struct RenderScene scene;
    int status;
} ng;

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

int
main(void)
{
    engine_start();

    while (ng.status == ENGINE_ON)
    {
        render_frame(&ng.window, &ng.scene, &engine_off);
    }

    engine_stop();

    return 0;
}

