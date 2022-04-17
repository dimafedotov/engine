#include <stdlib.h>
#include <stdio.h>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include <mruby.h>
#include <mruby/array.h>
#include <mruby/compile.h>

int main(void)
{
    GLFWwindow* window;

    int wWidth = 1280;
    int wHeight = 720;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(wWidth, wHeight, "Reserve Engine", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // VSync
    glClearColor(.12f, .12f, .12f, .0f);

    mrb_state *mrb = mrb_open();
    FILE *f = fopen("config.rb", "r");
    mrb_value _ = mrb_load_file(mrb, f);
    fclose(f);

    int code = 0;
    mrb_value geometry = mrb_funcall(mrb, mrb_top_self(mrb), "geometry", 0);

    if (mrb->exc)
    {
        printf("Runtime exception!\n");
        mrb_print_error(mrb);
        printf("\n\n");
    }

    switch (mrb_type(geometry))
    {
        case MRB_TT_ARRAY:
            printf("Loaded type: Array\n");
            break;
        case MRB_TT_SYMBOL:
            printf("Loaded type: Symbol\n");
            break;
        case MRB_TT_FIXNUM:
            printf("Loaded type: Fixnum\n");
            break;
        case MRB_TT_UNDEF:
            printf("Loaded type: Undefined\n");
            break;
        default:
            printf("Type recognition error!\n");
    }




    double t = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        t = glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT);

        // Select and setup the projection matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(65.f, (GLfloat) wWidth / (GLfloat) wHeight, 1.f, 100.f);

        // Select and setup the modelview matrix
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();
        gluLookAt(0.f, 1.f, 0.f,    // Eye-position
                  0.f, 20.f, 0.f,   // View-point
                  0.f, 0.f, 1.f);   // Up-vector

        // Draw a rotating colorful triangle
        glTranslatef(0.f, 14.f, 0.f);
        glRotatef(0.3f * (GLfloat) 1 + (GLfloat) t * 100.f, 0.f, 0.f, 1.f);

        glBegin(GL_TRIANGLES);
        glColor3f(.6f, .6f, .6f);

        mrb_value vertex;
        int idx = 0;
        while (mrb_type(mrb_ary_entry(geometry, idx)) == MRB_TT_ARRAY)
        {
            vertex = mrb_ary_entry(geometry, idx);
            float vx = mrb_float(mrb_ary_entry(vertex, 0));
            float vy = mrb_float(mrb_ary_entry(vertex, 1));
            float vz = mrb_float(mrb_ary_entry(vertex, 2));
            glVertex3f(vx, vy, vz);

            idx++;
        }

        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    mrb_close(mrb);
    glfwTerminate();
    return 0;
}

