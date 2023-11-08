#include <drn/dorian.hpp>
#include <drn/scene.hpp>
#include <drn/luanode.hpp>
#include <iostream>

using namespace drn;

Window GameWindow("Dorian Engine", 1080, 720);

#ifndef DORIAN_INITSCENE
HLScene TestScene;

Image TestImage("testImage.png");

class TestCube : public Node {
    public:
    float rX = 0;
    void init() {
        TestImage.Init(GL_TEXTURE0);
    }
    void update() {
        rX += GameWindow.getDT();
    }
    void draw() {
        TestImage.UseImage(GL_TEXTURE0);
        drn::DrawRect({100, 100}, {100, 100});
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