#ifndef DORIAN_UI
#define DORIAN_UI

#include "scene.hpp"
#include "graphics.hpp"
#include <string>

namespace drn {
    class UIComponent {
        protected:
        Anchor m_AnchorTo;
        Vec2<int> m_Pos;
        Vec2<int> m_Size;
        Window* m_WindowP;

        public:
        UIComponent(Vec2<int> pos, Vec2<int> size, Window* window, Anchor a) {
            m_WindowP = window;
            m_AnchorTo = a;
            m_Size = size;
            m_Pos = pos;
        };

        virtual void Draw() {};
        virtual bool Update() {return false;};
    };

    class Label: public UIComponent {
        public:
        std::string Text{""};

        Label(Vec2<int> pos, std::string text, Window* window, Anchor a): UIComponent(pos, Vec2<int>{(int)text.length()*10, 18}, window, a) {
            Text = text;
        };

        Label(Vec2<int> pos, std::string text, Window* window): Label(pos, text, window, TopLeft) {};
        
        virtual void Draw() {
            DrawText(Text, m_WindowP->AnchorOnScreen(m_Pos, m_Size, m_AnchorTo));
        }
    };

    class UIImage: public UIComponent {
        private:
        Image* m_Image;
        float m_scale;
        
        public:

        UIImage(Image* img, Vec2<int> pos, Window* window): UIComponent(pos, {1, 1}, window, TopLeft) {
            m_Image = img;
            m_Size = m_Image->GetDimensions();
            m_scale = 1;
        }

        void resize(int s) {
            m_scale = s;
        }

        virtual void Draw() {
            if (m_AnchorTo == TopLeft)
                m_Image->Draw(m_Pos, m_scale);
        }
    };

    class Button: public UIComponent {
        private:
        RGB m_ButtonBGColor{255, 255, 255};

        public:
        std::string Text{""};

        Button(Vec2<int> pos, Vec2<int> size, Window* window, Anchor a): UIComponent(pos, size, window, a) {};
        Button(Vec2<int> pos, Vec2<int> size, Window* window): UIComponent(pos, size, window, TopLeft) {};

        virtual void Draw() {
            Vec2<int> textpos{m_WindowP->AnchorOnScreen(m_Pos, m_Size, m_AnchorTo)};
            DrawRect(m_WindowP->AnchorOnScreen(m_Pos, m_Size, m_AnchorTo), m_Size, m_ButtonBGColor);
            DrawText(Text, {textpos.X + m_Size.X/2 - (int)(Text.size()*9/2), textpos.Y + m_Size.Y/2 - 9}, {0, 0, 0});
        };
        virtual bool Update();
    };    
}

#endif