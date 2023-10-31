#ifndef DORIAN_SCENE
#define DORIAN_SCENE

#include "dorian.hpp"
#include "graphics.hpp"

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
        Vec3<float> Rotation = ZERO_VECTOR;
    };

    // A Low Level Scene for Low Level Programming
    // Used for Manually Programming your own Loop Functions
    // No nodes are used in this components. if you would like to use those, use HLScene
    class LLScene: public Scene {
        private:
        int (*M_InitPF)();
        int (*M_DrawPF)();
        int (*M_UpdatePF)();

        public:
        LLScene(int initfunc (), int drawfunc (), int updatefunc ());

        void Init() { (*M_InitPF)(); };
        void Update() { (*M_UpdatePF)(); };
        void Draw() { (*M_DrawPF)(); };
    };


    // A High Level Scene for Multiple Objects in a scene
    // Add nodes to your Scene and have them all run together effortlessly
    // If you need to go more complex, I would suggest LLScene
    class HLScene: public Scene {
        public:
        // Camera Reference Point Variable. not 100% sure about this idea yet.
        Node* CameraPerspective;


        std::vector<Node*> WorldComponents;

        void Init() {
            for (Node* n : WorldComponents) n->init();
        };
        void Update() {
            for (Node* n : WorldComponents) n->update();
        };
        void Draw();

        //Vec2<int> ProjectPerspective(Vec3<float> pos);
    };
}

#endif