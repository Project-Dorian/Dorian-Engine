#include <drn/dorian.hpp>
#include <drn/graphics.hpp>
#include <drn/scene.hpp>

using namespace drn;

Window GameWindow;


HLScene EmptyScene;

int nodecount = 0;

class TestNode : public drn::Node {
    public:
    Vec2<int> pos = ZERO_VECTOR;

    virtual void init() {
        pos.X += 20*nodecount++;
    }
    
    virtual void draw() {
        drn::DrawRect(pos, {10, 10});
    }
};

TestNode Object;
TestNode Object2;
TestNode Object3;
TestNode Object4;

int main() {
    EmptyScene.WorldComponents.push_back(&Object);
    EmptyScene.WorldComponents.push_back(&Object2);
    EmptyScene.WorldComponents.push_back(&Object3);
    EmptyScene.WorldComponents.push_back(&Object4);
    
    GameWindow.Init(&EmptyScene);

    GameWindow.Loop();

    return 0;
}