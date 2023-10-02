#ifndef DORIAN_SCENE
#define DORIAN_SCENE

#include "dorian.hpp"
#include "ui.hpp"

namespace drn {

    class Node {
        public:
        virtual void init() {};
        virtual void update() {};
        virtual void draw() {};

        virtual ~Node() {};
    };

    class ObjectNode: public Node {
        public:
        Vec3<float> position = ZERO_VECTOR;
    };

    // A Low Level Scene for Low Level Programming
    // Used for Manually Programming your own Loop Functions
    // No nodes are used in this components. if you would like to use those, use HLScene
    class LLScene: public Scene {
        private:
        int (*M_InitPF)();
        int (*M_DrawPF)(int);
        int (*M_UpdatePF)(int);

        int m_InitState{0};

        public:
        LLScene(int initfunc (), int drawfunc (int), int updatefunc (int));

        virtual void Init() { m_InitState = (*M_InitPF)(); };
        virtual void Update() { (*M_UpdatePF)(m_InitState); };
        virtual void Draw() { (*M_DrawPF)(m_InitState); };
    };


    // A High Level Scene for Multiple Objects in a scene
    // Add nodes to your Scene and have them all run together effortlessly
    // If you need to go more complex, I would suggest LLScene
    class HLScene: public Scene {
        public:
        std::vector<Node*> WorldComponents;

        virtual void Init() {
            for (Node* n : WorldComponents) n->init();
        };
        virtual void Draw() {
            for (Node* n : WorldComponents) n->draw();
        };
        virtual void Update() {
            for (Node* n : WorldComponents) n->update();
        };
    };
}

#endif