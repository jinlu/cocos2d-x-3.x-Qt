#ifndef LUA2C_H
#define LUA2C_H

#include "CCLuaEngine.h"

class Lua2C
{
public:
    Lua2C();
    static int getIntValue(lua_State* L, const char* code);
    static bool getBoolValue(lua_State* L, const char *code);
    static const char* getStringValue(lua_State* L, const char *code);
};

#endif // LUA2C_H
