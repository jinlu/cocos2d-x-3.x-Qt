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


