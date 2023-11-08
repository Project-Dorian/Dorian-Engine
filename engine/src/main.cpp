#include <drn/dorian.hpp>
#include <drn/scene.hpp>
#include <drn/luanode.hpp>
#include <iostream>

using namespace drn;

Window GameWindow("Dorian Engine", 1080, 720);

#ifndef DORIAN_INITSCENE
HLScene TestScene;

Image TestImage("testImage.jpg");

class TestCube : public Node {
    public:
    float rX = 0;
    void init() {
        TestImage.Init();
    }
    void update() {
        rX += GameWindow.getDT();
    }
    void draw() {
        TestImage.UseImage(GL_TEXTURE0);
        drn::DrawCube({100, 100, 0}, {100, 100, 100}, {-30, 0, rX});
    };
};

TestCube Cube;
LuaNode TestObject("testluaobject.lua");

#define DORIAN_INITSCENE TestScene
#endif

Scene EmptyScene;

int SDL_main(int argv, char** args) {
    TestScene.WorldComponents.push_back(&Cube);
    //TestScene.WorldComponents.push_back(&TestObject);
    int response = GameWindow.Init(&DORIAN_INITSCENE);
    if (response != 0) return response;

    GameWindow.Loop();

    return 0;
}