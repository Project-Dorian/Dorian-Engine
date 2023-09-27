#ifndef DORIAN_GRAPHICS
#define DORIAN_GRAPHICS

#include "dorian.hpp"
#include "vec.hpp"
#include "../raylib.h"

#include <string>

#define DORIAN_IMAGETYPE Texture2D

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

    extern void DrawSprite();

    extern void DrawRect(Vec2<int> pos, Vec2<int> size);
    extern void DrawRect(Vec2<int> pos, Vec2<int> size, RGB rgb);
    extern void DrawRect(Vec2<int> pos, Vec2<int> size, RGBA rgba);

    extern void DrawText(std::string text, Vec2<int> pos);
    extern void DrawText(std::string text, Vec2<int> pos, RGB rgb);
    
    extern void FillBG(RGB rgb);
    extern void FillBG(RGBA rgba);

    class Image {
        private:
        DORIAN_IMAGETYPE m_imgData;

        public:
        Image() {};
        Image(std::string src);
        //~Image();

        void Draw(Vec2<int> screenPos);
        void Draw(Vec2<int> screenPos, float Scale);

        // Draws the texture to the center of the point specified
        void DrawCenter(Vec2<int> screenPos);
        void DrawCenter(Vec2<int> screenPos, float Scale);

        Vec2<int> GetDimensions() {return {m_imgData.width, m_imgData.height};};
    };
}

#endif