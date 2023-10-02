#include <drn/dorian.hpp>
#include <drn/graphics.hpp>
#include <drn/scene.hpp>
#include <drn/luanode.hpp>

using namespace drn;

Window GameWindow;

HLScene EmptyScene;

int nodecount = 0;

LuaNode Object("testluaobject.lua");

int main() {
    EmptyScene.WorldComponents.push_back(&Object);
    
    GameWindow.Init(&EmptyScene);

    GameWindow.Loop();

    return 0;
}