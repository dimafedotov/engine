#include <stdlib.h>
#include <stdio.h>

#include <mruby.h>
#include <mruby/array.h>
#include <mruby/compile.h>

#include "render.h"

#define ENGINE_ON 1
#define ENGINE_OFF -1

struct Engine {
    struct RenderWindow window;
    struct RenderScene scene;
    int status;
    mrb_state *runtime;
} ng;

void
engine_start()
{
    ng.status = ENGINE_ON;

    ng.window.width = 1280;
    ng.window.height = 720;
    render_setup(&ng.window);

    mrb_state *mrb = ng.runtime;
    mrb = mrb_open();
    FILE *f = fopen("config.rb", "r");
    mrb_value _ = mrb_load_file(mrb, f);
    fclose(f);

    mrb_value geometry = mrb_funcall(mrb, mrb_top_self(mrb), "geometry", 0);

    if (mrb->exc)
    {
        printf("Runtime exception!\n");
        mrb_print_error(mrb);
        printf("\n\n");
    }

    mrb_value vertex;
    int idx = 0;
    while (mrb_type(mrb_ary_entry(geometry, idx)) == MRB_TT_ARRAY)
    {
        vertex = mrb_ary_entry(geometry, idx);
        ng.scene.vertices[idx][0] = mrb_float(mrb_ary_entry(vertex, 0));
        ng.scene.vertices[idx][1] = mrb_float(mrb_ary_entry(vertex, 1));
        ng.scene.vertices[idx][2] = mrb_float(mrb_ary_entry(vertex, 2));
        idx++;
    }
}

void
engine_stop()
{
    mrb_close(ng.runtime);
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

