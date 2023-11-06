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

    extern GLchar* DefaultVertexShader[];
    extern GLchar* DefaultFragmentShader[];

    class Shader {
        private:
        GLuint m_VertexShader;
        GLuint m_FragmentShader;
        GLuint m_GLProgramID;

        public:
        Shader(GLchar** FragmentCode, GLchar** VertexCode);
        Shader(GLchar** FragmentCode): Shader(FragmentCode, DefaultVertexShader) {};
        Shader() {};

        GLuint getProgramID() {return m_GLProgramID;};
        void UseShader() {glUseProgram(m_GLProgramID);};
    };

    extern Shader DefaultShader;
    extern Shader* CurrentShader;


    //extern void DrawSprite();

    extern void DrawQuad(Vec2<float> a, Vec2<float> b, Vec2<float> c, Vec2<float> d);

    extern void DrawRect(Vec2<float> pos, Vec2<float> size);
    //extern void DrawRect(Vec2<int> pos, Vec2<int> size, RGB rgb);
    //extern void DrawRect(Vec2<int> pos, Vec2<int> size, RGBA rgba);

    //extern void DrawText(std::string text, Vec2<int> pos);
    //extern void DrawText(std::string text, Vec2<int> pos, RGB rgb);

    // 3D Equations
    extern void DrawPlane(Vec3<float> a, Vec3<float> b, Vec3<float> c, Vec3<float> d);

    //extern void DrawLine(Vec2<int> start, Vec2<int> end);
    
    //extern void FillBG(RGB rgb);
    //extern void FillBG(RGBA rgba);

    class Texture {

    };
}

#endif