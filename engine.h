#ifndef ENGINE_H
#define ENGINE_H

#include "render.h"

struct Engine {
    struct RenderWindow window;
    struct RenderScene scene;
    int status;
} ng;

#endif
