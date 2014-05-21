#include "lua_cocos2dx_bridge_auto.hpp"
#include "luabridge.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_cocos2dx_bridge_LuaBridge_getPath(lua_State* tolua_S)
{
    int argc = 0;
    LuaBridge* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"LuaBridge",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (LuaBridge*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_bridge_LuaBridge_getPath'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const char* ret = cobj->getPath();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getPath",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_bridge_LuaBridge_getPath'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_bridge_LuaBridge_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"LuaBridge",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        LuaBridge* ret = LuaBridge::getInstance();
        object_to_luaval<LuaBridge>(tolua_S, "LuaBridge",(LuaBridge*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_bridge_LuaBridge_getInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_bridge_LuaBridge_constructor(lua_State* tolua_S)
{
    int argc = 0;
    LuaBridge* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new LuaBridge();
        tolua_pushusertype(tolua_S,(void*)cobj,"LuaBridge");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "LuaBridge",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_bridge_LuaBridge_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_bridge_LuaBridge_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (LuaBridge)");
    return 0;
}

int lua_register_cocos2dx_bridge_LuaBridge(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"LuaBridge");
    tolua_cclass(tolua_S,"LuaBridge","LuaBridge","",nullptr);

    tolua_beginmodule(tolua_S,"LuaBridge");
        tolua_function(tolua_S,"getPath",lua_cocos2dx_bridge_LuaBridge_getPath);
        tolua_function(tolua_S,"new",lua_cocos2dx_bridge_LuaBridge_constructor);
        tolua_function(tolua_S,"getInstance", lua_cocos2dx_bridge_LuaBridge_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(LuaBridge).name();
    g_luaType[typeName] = "LuaBridge";
    g_typeCast["LuaBridge"] = "LuaBridge";
    return 1;
}
TOLUA_API int register_all_cocos2dx_bridge(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"dd",0);
	tolua_beginmodule(tolua_S,"dd");

	lua_register_cocos2dx_bridge_LuaBridge(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

