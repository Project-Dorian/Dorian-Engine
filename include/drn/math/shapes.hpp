#ifndef DORIAN_SHAPES
#define DORIAN_SHAPES

#include "vec.hpp"

namespace drn {
    // Generates the vertices of a 2D polygon made of triangles based on the number of sides input.
    // See docs/shapes.md for more info
    extern drn::Vec2<float>* PolygonVerts2D(int s);
    
    // Generates the edges of a 2D polygon made of triangles based on the number of sides input.
    // See docs/headers/shapes.md for more info
    extern int* PolygonEdges2D(int s);
}

#endif