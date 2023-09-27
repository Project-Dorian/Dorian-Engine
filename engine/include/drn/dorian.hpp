#ifndef DORIAN_MAIN
#define DORIAN_MAIN

#include "../raylib.h"
#include "vec.hpp"
#include <vector>
#include <string>

#ifndef DWINDOW_WIDTH
#define DWINDOW_WIDTH 1080
#endif

#ifndef DWINDOW_HEIGHT
#define DWINDOW_HEIGHT 720
#endif

typedef char          i8;
typedef short         i16;
typedef int           i32;
typedef long int      i64;
typedef long long int i128;

typedef unsigned char          ui8;
typedef unsigned short         ui16;
typedef unsigned int           ui32;
typedef unsigned long int      ui64;
typedef unsigned long long int ui128;

namespace drn {

    // Generic Empty Scene
    // Mostly used for testing purposes
    class Scene {
        public:
        virtual void Init() {};
        virtual void Update() {};
        virtual void Draw() {};
    };

    enum Anchor {TopLeft, Top, TopRight, Left, Center, Right, BottomLeft, Bottom, BottomRight};

    // The Default Window Class of the Dorian Engine
    class Window {
        private:
        Scene* m_CurrentScene;
        float m_CurrentDT;

        std::string m_WindowName;
        i32 m_windowWidth;
        i32 m_windowHeight;

        public:
        // Constructor
        Window(std::string title, i32 width, i32 height);
        Window(std::string title): Window(title, DWINDOW_WIDTH, DWINDOW_HEIGHT) {};

        // The Generic Window Class Constructor
        Window(): Window("Dorian Engine", DWINDOW_WIDTH, DWINDOW_HEIGHT) {};
        
        float getDT();
        // Load a Scene into the game
        void LoadScene(Scene*);
        // Call this to officially initialize the game
        void Init(Scene*);
        // The primary loop function of a Dorian Window
        void Loop();

        Vec2<i32> GetWindowDimensions() {return {m_windowWidth, m_windowHeight};};

        // TODO: Get the rest of the anchors programmed in the game.
        // They are not needed for this game specifically, but could help in the future
        Vec2<int> AnchorOnScreen(Vec2<int> padding, Vec2<int> size, Anchor anchor) {
            // Please fill this in properly
            switch (anchor) {
                case TopRight:
                    return {m_windowWidth - padding.X - size.X, padding.Y};
                case BottomLeft:
                    return {padding.X, m_windowHeight - padding.Y - size.Y};
                case BottomRight:
                    return {m_windowWidth - padding.X - size.X, m_windowHeight - padding.Y - size.Y};
            }

            // Default Case TopLeft
            return padding;
        }
    };
}

#endif