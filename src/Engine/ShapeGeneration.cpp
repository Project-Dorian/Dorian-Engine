#include <drn/math/shapes.hpp>

#include <map>
#include <math.h>
#define M_PI 3.14159265

std::map<int, drn::Vec2<float>*> PolygonVertexData2D;
std::map<int, int*> PolygonEdgeData2D;

std::map<drn::Vec2<int>, drn::Vec3<float>*> SphereVertexData;
std::map<drn::Vec2<int>, int*> SphereEdgeData;

drn::Vec2<float>* drn::PolygonVerts2D(int s) {
    // Check first if the polygon vertex data exists
    if (PolygonVertexData2D.count(s)) return PolygonVertexData2D.at(s);

    drn::Vec2<float>* output = new drn::Vec2<float>[s+1];
    output[0] = ZERO_VECTOR;

    for (int i = 0; i < s; i++) {
        output[i+1] = {cosf(M_PI*2*i/s), sinf(M_PI*2*i/s)};
    }

    PolygonVertexData2D.insert({s, output});
    return output;
}

int* drn::PolygonEdges2D(int s) {
    // Check first if the polygon edge data exists
    if (PolygonEdgeData2D.count(s)) return PolygonEdgeData2D.at(s);
    
    int* output = new int[s*3];

    int i = 0;
    while (i < s) {
        output[i*3] = 0;
        output[i*3+1] = i+1;
        output[i*3+2] = (++i)+1;
    }

    PolygonEdgeData2D.insert({s, output});
    return output;
}

drn::Vec3<float>* drn::SphereVerts(int r, int c) {
    // Check first if the polyhedron vertex data exists
    if (SphereVertexData.count({r, c})) return SphereVertexData.at({r, c});

    drn::Vec3<float>* output = new drn::Vec3<float>[r*c];

    for (int i=0; i < r; i++) {
        for (int j=0; j < c; j++) {
            output[r*i+j] = {
                cosf(M_PI*2*i/r)*sinf(M_PI*j/c),
                sinf(M_PI*2*i/r)*sinf(M_PI*j/c),
                sinf(M_PI*j/c)
            };
        }
    }

    SphereVertexData.insert({{r, c}, output});
    return output;
}

int* drn::SphereEdges(int r, int c) {
    if (SphereEdgeData.count({r, c})) return SphereEdgeData.at({r, c});
    
    int* output = new int[r*c*6];

    int vert = 0;
    int tris = 0;

    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 20; x++) {
            output[tris] = vert;
            output[tris + 2] = vert + r + 1;
            output[tris + 1] = vert + 1;
            output[tris + 3] = vert + 1;
            output[tris + 5] = vert + r + 1;
            output[tris + 4] = vert + r + 2;

            vert++;
            tris += 6;
        }
    }

    return output;
}

void drn::CleanPolygonData() {
    // Clearing Vertex Data
    for (auto& [k, v] : PolygonVertexData2D) {
        delete[] v;
    }
    PolygonVertexData2D.clear();

    // Clearing Edge Data
    for (auto& [k, v] : PolygonEdgeData2D) {
        delete[] v;
    }
    PolygonEdgeData2D.clear();
}