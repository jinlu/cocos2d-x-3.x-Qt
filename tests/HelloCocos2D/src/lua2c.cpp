#include "lua2c.h"
#include "stdio.h"

Lua2C::Lua2C()
{

}

int Lua2C::getIntValue(lua_State*L, const char* code)
{
    if (code == NULL || strlen(code) == 0)
    {
        return 0;
    }

    char buff[512];
    sprintf(buff,"return %s",code);
    int ret = luaL_dostring(L, buff);
    if (ret == 1)
    {
        printf("Lua2C::getIntValue error code : %s", code);
        return 0;
    }

    int retValue = lua_tointeger(L,-1);
    lua_pop(L,-1);

    return retValue;
}

bool Lua2C::getBoolValue(lua_State* L, const char *code)
{
    if (code == NULL || strlen(code) == 0)
    {
        return 0;
    }

    char buff[512];
    sprintf(buff,"return %s",code);
    int ret = luaL_dostring(L, buff);
    if (ret == 1)
    {
        printf("Lua2C::getIntValue error code : %s", code);
        return 0;
    }

    int retValue = lua_toboolean(L,-1);
    lua_pop(L,-1);

    return retValue;
}

const char* Lua2C::getStringValue(lua_State*L, const char *code)
{
    if (code == NULL || strlen(code) == 0)
    {
        return "";
    }

    char buff[512];
    sprintf(buff,"return %s",code);
    int ret = luaL_dostring(L, buff);
    if (ret == 1)
    {
        printf("Lua2C::getStringValue error code : %s", code);
        return 0;
    }

    const char *retValue = lua_tostring(L,-1);
    lua_pop(L,-1);

    return retValue;
}

const char* Lua2C::getPointValue(lua_State* L, const char *code)
{
    if (code == NULL || strlen(code) == 0)
    {
        return "";
    }

    char buff[512];
    sprintf(buff,"return %s.x, %s.y",code,code);
    int ret = luaL_dostring(L, buff);
    if (ret == 1)
    {
        printf("Lua2C::getPointValue error code : %s", code);
        return 0;
    }

    char retValue[512];
    const char *x = lua_tostring(L,-2);
    const char *y = lua_tostring(L,-1);
    sprintf(retValue,"%s,%s",x,y);
    lua_pop(L,-1);

    return retValue;
}

