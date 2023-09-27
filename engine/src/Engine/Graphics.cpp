#include <drn/graphics.hpp>
#include <drn/ui.hpp>

using namespace drn;

// Basic Graphics Drawing
void drn::DrawRect(drn::Vec2<int> pos, drn::Vec2<int> size) {
    DrawRectangle(pos.X, pos.Y, size.X, size.Y, WHITE);
}

void drn::DrawRect(drn::Vec2<int> pos, drn::Vec2<int> size, RGB rgb) {
    DrawRectangle(pos.X, pos.Y, size.X, size.Y, {rgb.R, rgb.G, rgb.B, 255});
}

void drn::DrawRect(drn::Vec2<int> pos, drn::Vec2<int> size, RGBA rgba) {
    DrawRectangle(pos.X, pos.Y, size.X, size.Y, {rgba.R, rgba.G, rgba.B, rgba.A});
}

void drn::DrawText(std::string text, drn::Vec2<int> pos) {
    ::DrawText(text.c_str(), pos.X, pos.Y, 18, WHITE);
}

void drn::DrawText(std::string text, drn::Vec2<int> pos, RGB rgb) {
    ::DrawText(text.c_str(), pos.X, pos.Y, 18, {rgb.R, rgb.G, rgb.B, 255});
}

void drn::FillBG(RGBA rgba) {
    Color SampleColor{rgba.R, rgba.G, rgba.B, rgba.A};

    ClearBackground(SampleColor);
}

// Images
drn::Image::Image(std::string src) {
    m_imgData = LoadTexture(src.c_str());
}

// drn::Image::~Image() {
    // UnloadTexture(m_imgData);
// }

void drn::Image::Draw(drn::Vec2<int> screenPos) {
    DrawTexture(m_imgData, screenPos.X, screenPos.Y, WHITE);
}

void drn::Image::Draw(drn::Vec2<int> screenPos, float Scale) {
    DrawTextureEx(m_imgData, {(float)(screenPos.X), (float)(screenPos.Y)}, 0, Scale, WHITE);
}

void drn::Image::DrawCenter(drn::Vec2<int> screenPos) {
    DrawTexture(m_imgData, screenPos.X - m_imgData.width/2, screenPos.Y - m_imgData.height/2, WHITE);
}

void drn::Image::DrawCenter(drn::Vec2<int> screenPos, float Scale) {
    DrawTextureEx(m_imgData, {(float)(screenPos.X - m_imgData.width/2*Scale), (float)(screenPos.Y - m_imgData.height/2*Scale)}, 0, Scale, WHITE);
}

// UI Components

bool drn::Button::Update() {
    drn::Vec2<int> anchoredPos = m_WindowP->AnchorOnScreen(m_Pos, m_Size, m_AnchorTo);
    if (GetMouseX() >= anchoredPos.X && GetMouseX() <= anchoredPos.X + m_Size.X) {
        if (GetMouseY() >= anchoredPos.Y && GetMouseY() <= anchoredPos.Y + m_Size.Y) {
            m_ButtonBGColor = {155, 155, 155};
            
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return true;
        }
    } else {m_ButtonBGColor = {255, 255, 255};}
    return false;
}