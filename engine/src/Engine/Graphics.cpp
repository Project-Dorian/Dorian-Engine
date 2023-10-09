#include <drn/graphics.hpp>
#include <SDL2/SDL_opengl.h>

namespace drn {
    extern Window* WindowPT;
}

void drn::DrawRect(Vec2<float> pos, Vec2<float> size) {

    Vec2<float> newPos{pos.X/WindowPT->GetWindowDimensions().X, pos.Y/WindowPT->GetWindowDimensions().Y};
    Vec2<float> newSize{size.X/WindowPT->GetWindowDimensions().X, size.Y/WindowPT->GetWindowDimensions().Y};

    glBegin(GL_QUADS);
    glVertex2f(newPos.X, newPos.Y);
    glVertex2f(newPos.X+newSize.X, newPos.Y);
    glVertex2f(newPos.X+newSize.X, newPos.Y-newSize.Y);
    glVertex2f(newPos.X, newPos.Y-newSize.Y);
    glEnd();
}