#ifndef DORIAN_GRAPHICS
#define DORIAN_GRAPHICS

#include "dorian.hpp"
#include "vec.hpp"
#include <GL/glew.h>

#include <string>

namespace drn {
    //-------------------//
    // Graphic Datatypes //
    //-------------------//

    struct RGB {
        unsigned char R;
        unsigned char G;
        unsigned char B;
    };

    struct RGBA {
        unsigned char R;
        unsigned char G;
        unsigned char B;
        unsigned char A;
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

    // Images

    struct SpriteCoords {
        int x;
        int y;
        int w;
        int h;
    };

    // A general image object where you can take any .png file and use it as a spritesheet,  
    class Image {
        private:
        int m_Width;
        int m_Height;
        int m_nrChannels;

        unsigned int m_glTexture;

        std::vector<SpriteCoords> m_imgCoords;
        
        unsigned char* m_imgData;

        public:
        Image(char* ImageName, std::vector<SpriteCoords> imgCoords);
        Image(char* ImageName): Image(ImageName, {{0, 0, 0, 0}}) {};

        void Init();

        ~Image();

        void UseImage(GLenum);
    };

    //extern void DrawSprite();

    extern void DrawQuad(Vec2<float> a, Vec2<float> b, Vec2<float> c, Vec2<float> d);

    extern void DrawRect(Vec2<float> pos, Vec2<float> size);
    //extern void DrawRect(Vec2<int> pos, Vec2<int> size, RGB rgb);
    //extern void DrawRect(Vec2<int> pos, Vec2<int> size, RGBA rgba);

    //extern void DrawText(std::string text, Vec2<int> pos);
    //extern void DrawText(std::string text, Vec2<int> pos, RGB rgb);

    // 3D Equations

    // Draws a plane that covers the area of |AB x AC|
    extern void DrawPlane(Vec3<float> a, Vec3<float> b, Vec3<float> c, Vec3<float> d);

    extern void DrawCube(Vec3<float> pos, Vec3<float> size, Vec3<float> rotation);
    extern void DrawCube(Vec3<float>, Vec3<float>);

    //extern void DrawLine(Vec2<int> start, Vec2<int> end);
    
    //extern void FillBG(RGB rgb);
    //extern void FillBG(RGBA rgba);
}

#endif