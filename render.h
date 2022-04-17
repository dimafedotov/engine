#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#define RENDER_OK 0
#define RENDER_ERROR -1

struct RenderWindow {
    GLFWwindow *hwnd;
    int width;
    int height;
};

struct RenderScene {
    int vertices[3][3];
};

int
render_setup(struct RenderWindow *window)
{
    if (!glfwInit())
        return RENDER_ERROR;

    window->hwnd = glfwCreateWindow(window->width, window->height, "Reserve Engine", NULL, NULL);

    if (!window->hwnd)
    {
        glfwTerminate();
        return RENDER_ERROR;
    }

    glfwMakeContextCurrent(window->hwnd);
    glfwSwapInterval(1); // VSync
    glClearColor(.12f, .12f, .12f, .0f);

    return RENDER_OK;
}

double
render_frame(struct RenderWindow *window, struct RenderScene *scene, void (*close)())
{
    double t = glfwGetTime();

    glClear(GL_COLOR_BUFFER_BIT);

    // Select and setup the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.f, (GLfloat) window->width / (GLfloat) window->height, 1.f, 100.f);

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
    for(int i = 0; i<3; i++)
    {
        glVertex3f(
            scene->vertices[i][0],
            scene->vertices[i][1],
            scene->vertices[i][2]
        );
    }
    glEnd();

    glfwSwapBuffers(window->hwnd);
    glfwPollEvents();

    if (glfwWindowShouldClose(window->hwnd))
    {
        glfwTerminate();
        close();
    }

    return t;
}
