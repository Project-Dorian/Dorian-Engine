#include <drn/dorian.hpp>
#include <drn/scene.hpp>
#include <drn/luanode.hpp>
#include <iostream>

using namespace drn;

Window GameWindow("Game Name");

#ifndef DORIAN_INITSCENE
HLScene TestScene;
LuaNode Cube("spinningcube.lua");
#define DORIAN_INITSCENE TestScene
#endif

Scene EmptyScene;

int SDL_main(int argv, char** args) {
    TestScene.WorldComponents.push_back(&Cube);
    int response = GameWindow.Init(&DORIAN_INITSCENE);
    if (response != 0) return response;
    InitGLShaders();

    GameWindow.Loop();

    return 0;
}