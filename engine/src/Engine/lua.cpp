#include <drn/luanode.hpp>
#include <drn/input.hpp>

namespace drn {
    extern Window* WindowPT;
}

using namespace drn;

//---------------//
// LUA FUNCTIONS //
//---------------//

int l_getDT(lua_State *L) {
    lua_pushnumber(L, WindowPT->getDT());
    return 1;
}

int l_getWindowWidth(lua_State *L) {
    lua_pushnumber(L, WindowPT->GetWindowDimensions().X);
    return 1;
}

int l_getWindowHeight(lua_State *L) {
    lua_pushnumber(L, WindowPT->GetWindowDimensions().Y);
    return 1;
}

// Graphics 

int l_drawRectangle(lua_State *L) {
    float x = lua_tonumber(L, 1);
    float y = lua_tonumber(L, 2);
    float w = lua_tonumber(L, 3);
    float h = lua_tonumber(L, 4);

    DrawRect({x, y}, {w, h});
    return 0;
}

int l_drawLine(lua_State *L) {
    float x1 = lua_tonumber(L, 1);
    float y1 = lua_tonumber(L, 2);
    float x2 = lua_tonumber(L, 3);
    float y2 = lua_tonumber(L, 4);

    //drn::DrawLine({x1, y1}, {x2, y2});
    return 0;
}

int l_drawQuad(lua_State *L) {
    float x1 = lua_tonumber(L, 1);
    float y1 = lua_tonumber(L, 2);
    float x2 = lua_tonumber(L, 3);
    float y2 = lua_tonumber(L, 4);
    float x3 = lua_tonumber(L, 5);
    float y3 = lua_tonumber(L, 6);
    float x4 = lua_tonumber(L, 7);
    float y4 = lua_tonumber(L, 8);

    drn::DrawQuad({x1, y1}, {x2, y2}, {x3, y3}, {x4, y4});
    return 0;
}

// Input

int l_inputPressed(lua_State *L) {
    int i = lua_tointeger(L, 1);

    lua_pushboolean(L, InputPressed(i));
    return 1;
}

int l_inputReleased(lua_State *L) {
    int i = lua_tointeger(L, 1);

    lua_pushboolean(L, InputReleased(i));
    return 1;
}

int l_inputDown(lua_State *L) {
    int i = lua_tointeger(L, 1);

    lua_pushboolean(L, InputDown(i));
    return 1;
}

void lua_setup(lua_State* L) {
    lua_pushcfunction(L, l_getDT);
    lua_setglobal(L, "GetDeltaTime");

    lua_pushcfunction(L, l_getWindowWidth);
    lua_setglobal(L, "WindowWidth");

    lua_pushcfunction(L, l_getWindowHeight);
    lua_setglobal(L, "WindowHeight");

    // Graphics
    lua_pushcfunction(L, l_drawRectangle);
    lua_setglobal(L, "DrawRect");

    lua_pushcfunction(L, l_drawLine);
    lua_setglobal(L, "DrawLine");

    lua_pushcfunction(L, l_drawQuad);
    lua_setglobal(L, "DrawQuad");

    // Input
    lua_pushcfunction(L, l_inputDown);
    lua_setglobal(L, "InputDown");
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
    if (luaL_dofile(L, m_filename.c_str())) Debug_Warn("File " << m_filename.c_str() << " Not Found"); 
}

void LuaNode::draw() {
    lua_getglobal(L, "draw");
    lua_pcall(L, 0, 0, 0);
}

void LuaNode::update() {
    lua_getglobal(L, "update");
    lua_pcall(L, 0, 0, 0);
}

// LuaObjectNode

