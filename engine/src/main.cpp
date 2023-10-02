#include <drn/dorian.hpp>
#include <drn/graphics.hpp>
#include <drn/scene.hpp>
#include <drn/luanode.hpp>

namespace drn {
    extern Window* WindowPT;
}

using namespace drn;

Window GameWindow;
Window* WindowPT = &GameWindow;

HLScene EmptyScene;

int nodecount = 0;

LuaNode Object("testluaobject.lua");

int main() {
    EmptyScene.WorldComponents.push_back(&Object);
    
    GameWindow.Init(&EmptyScene);

    GameWindow.Loop();

    return 0;
}