#ifndef DORIAN_LUANODE
#define DORIAN_LUANODE

#include "scene.hpp"
#include "../lua.hpp"
#include <string>

namespace drn {
    struct PackagedLuaScript {
        std::string data;
    };

    class LuaNode: public Node {
        private:
        lua_State *L;
        std::string m_filename;

        public:
        LuaNode(std::string file);
        //LuaNode(PackagedLuaScript script);

        virtual ~LuaNode();

        virtual void init();
        virtual void draw();
        virtual void update() {};
    };
}

#endif