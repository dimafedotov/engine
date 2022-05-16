#ifndef OBJECT_H
#define OBJECT_H

struct Vertex {
    float x;
    float y;
    float z;
    float u;
    float v;
};

struct Normal {
    float x;
    float y;
    float z;
};

// 128Mb for all faces ~ 7 millions
struct Face {
    struct Vertex a;
    struct Vertex b;
    struct Vertex c;
    struct Normal n;
};

struct Surface {
    int faces[62];
    int surface;
    unsigned short material;
    unsigned short reserved;
};

struct Object {
    int surface;
    int weight;
    float x;
    float y;
    float z;
};

#endif
