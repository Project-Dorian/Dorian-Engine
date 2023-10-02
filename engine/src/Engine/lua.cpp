#include <drn/luanode.hpp>

namespace drn {
    extern Window* WindowPT{nullptr};
}

using namespace drn;

//---------------//
// LUA FUNCTIONS //
//---------------//

int l_drawRectangle(lua_State *L) {
    int x = lua_tonumber(L, 1);
    int y = lua_tonumber(L, 2);
    int w = lua_tonumber(L, 3);
    int h = lua_tonumber(L, 4);

    DrawRect({x, y}, {w, h});
    return 0;
}

int l_getDT(lua_State *L) {
    lua_pushnumber(L, WindowPT->getDT());
    return 1;
}

void lua_setup(lua_State* L) {
    lua_pushcfunction(L, l_drawRectangle);
    lua_setglobal(L, "DrawRect");

    lua_pushcfunction(L, l_getDT);
    lua_setglobal(L, "GetDeltaTime");
}

//-----------//
// LUA NODES //
//-----------//

LuaNode::LuaNode(std::string file) {
    L = lua_open();
    luaL_openlibs(L);
    
    lua_setup(L);

    lua_newtable(L);

    m_filename = file;
}

LuaNode::~LuaNode() {
    lua_close(L);
}

void LuaNode::init() {
    luaL_dofile(L, m_filename.c_str());
}

void LuaNode::draw() {
    lua_getglobal(L, "draw");
    lua_pcall(L, 0, 0, 0);
}

void LuaNode::update() {
    lua_getglobal(L, "update");
    lua_pcall(L, 0, 0, 0);
}