#ifndef DORIAN_GRAPHICS
#define DORIAN_GRAPHICS

#include "dorian.hpp"
#include "vec.hpp"
#include <GL/glew.h>

#include <string>

#define DORIAN_IMAGETYPE SDL_Surface*

namespace drn {
    //----------------//
    // Basic Graphics //
    //----------------//

    struct RGB {
        ui8 R;
        ui8 G;
        ui8 B;
    };

    struct RGBA {
        ui8 R;
        ui8 G;
        ui8 B;
        ui8 A;
    };

    int InitGLShaders();
    extern GLuint DefaultVertexShader;
    extern GLuint DefaultFragmentShader;
    extern GLuint gProgramID;


    //extern void DrawSprite();

    extern void DrawRect(Vec2<float> pos, Vec2<float> size);
    //extern void DrawRect(Vec2<int> pos, Vec2<int> size, RGB rgb);
    //extern void DrawRect(Vec2<int> pos, Vec2<int> size, RGBA rgba);

    extern void DrawQuad(Vec2<float> a, Vec2<float> b, Vec2<float> c, Vec2<float> d);

    //extern void DrawText(std::string text, Vec2<int> pos);
    //extern void DrawText(std::string text, Vec2<int> pos, RGB rgb);

    //extern void DrawLine(Vec2<int> start, Vec2<int> end);
    
    //extern void FillBG(RGB rgb);
    //extern void FillBG(RGBA rgba);
}

#endif