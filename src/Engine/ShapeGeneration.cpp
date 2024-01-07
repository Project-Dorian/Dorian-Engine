#include <drn/math/shapes.hpp>

#include <math.h>
#define M_PI 3.14159265

drn::Vec2<float>* drn::PolygonVerts2D(int s) {
    drn::Vec2<float>* output = new drn::Vec2<float>[s+1];
    output[0] = ZERO_VECTOR;

    for (int i = 0; i < s; i++) {
        output[i+1] = {cosf(M_PI*2*i/s), sinf(M_PI*2*i/s)};
    }

    return output;
}

int* drn::PolygonEdges2D(int s) {
    int* output = new int[s*3];

    int i = 0;
    while (i <= s) {
        output[i*3] = 0;
        output[i*3+1] = i+1;
        output[i*3+2] = (++i)+1;
    }

    return output;
}