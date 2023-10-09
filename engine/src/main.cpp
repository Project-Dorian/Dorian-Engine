#include <drn/dorian.hpp>
#include <drn/scene.hpp>
#include <iostream>

using namespace drn;

Window GameWindow;

int emptyfunc() {return 0;}

int DrawTest() {
    DrawRect({0, 0}, {100, 100});
    return 0;
}

LLScene EmptyScene(emptyfunc, DrawTest, emptyfunc);

int SDL_main(int argv, char** args) {
    int response = GameWindow.Init(&EmptyScene);
    if (response != 0) return response;

    GameWindow.Loop();

    return 0;
}