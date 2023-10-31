#include <drn/input.hpp>

drn::BoolArray drn::KeyboardInput(2);

bool drn::InputPressed(int i) {
    //return IsKeyPressed(i);
    return 0;
}

bool drn::InputReleased(int i) {
    //return IsKeyReleased(i);
    return 0;
}

bool drn::InputDown(int i) {
    return KeyboardInput[i];
}