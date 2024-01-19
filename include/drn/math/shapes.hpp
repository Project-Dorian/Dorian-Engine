#ifndef DORIAN_SHAPES
#define DORIAN_SHAPES

#include "vec.hpp"

namespace drn {
    // Generates and/or returns the vertices of a 2D polygon made of triangles based on the number of sides input.
    // See docs/shapes.md for more info
    extern drn::Vec2<float>* PolygonVerts2D(int s);
    
    // Generates and/or returns the edges of a 2D polygon made of triangles based on the number of sides input.
    // See docs/headers/shapes.md for more info
    extern int* PolygonEdges2D(int s);

    // Generates and/or returns the vertices of a 3D Sphere made of triangles based on the number of rows and columns
    // See docs/shapes.md for more info
    extern drn::Vec3<float>* SphereVerts(int r, int c);

    // Generates and/or returns the edges of a 3D Sphere made of triangles based on the number of rows and columns
    // See docs/shapes.md for more info
    extern int* SphereEdges(int r, int c);

    // Frees the vertex and edge data stored in the heap by the polygon functions to avoid memory leaks
    // This is already called after the main loop closes, but feel free to call this whenever needed.
    extern void CleanPolygonData();
}

#endif