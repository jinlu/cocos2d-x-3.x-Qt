#include "uimanager.h"
#include "CCLuaEngine.h"
#include "lua_extensions.h"

UnitDataTable UnitData[] = {
  {"speed",   1, },
  {"discoverRadii",     1,},
  {"discoverOffset",   0, },
  {"hurtBasePoint",    0, },
  {"hurtVar",      0, }  /* sentinel */
};

/* assume that table is at the top */
void setfield (lua_State *L, const char *index, int value)
{
    lua_pushstring(L, index);
    lua_pushnumber(L, value);
    lua_settable(L, -3);
}

/* assume that table is on the stack top */
int getfield (lua_State *L, const char *key)
{
    int result;
    lua_pushstring(L, key);
    lua_gettable(L, -2);  /* get background[key] */
    if (!lua_isnumber(L, -1))
    {
    //     error(L, "invalid component in background color");
       CCLOG("invalid component in background color");
       exit(0);
    }
    result = (int)lua_tonumber(L, -1) ;
    lua_pop(L, 1);  /* remove number */
    return result;
}

UIManager::UIManager(MainWindow *mw, lua_State *state)
{
    mainWindow = mw;
    L = state;
}

void UIManager::getUnitData(struct UnitDataTable& table )
{
//    lua_getglobal(L, "color");
//    if (!lua_istable(L, -1))
//    {
//        CCLOG("`background' is not a valid color table");
//        exit(0);
//    }

//    int red = getfield(L,"r");
//    int green = getfield(L,"g");
//    int blue = getfield(L,"b");

//    table.red = red;
//    table.green = green;
//    table.blue = blue;
}

void UIManager::setUnitData()
{
    lua_newtable(L);

    lua_pushstring(L,"speed");
    lua_pushnumber(L,168);
    lua_settable(L,-3);

    lua_pushstring(L,"discoverRadii");
    lua_pushnumber(L,1);
    lua_settable(L,-3);

    lua_pushstring(L,"discoverOffset");
    lua_pushnumber(L,3);
    lua_settable(L,-3);

    lua_pushstring(L,"hurtBasePoint");
    lua_pushnumber(L,3);
    lua_settable(L,-3);

    lua_pushstring(L,"hurtVar");
    lua_pushnumber(L,3);
    lua_settable(L,-3);

    lua_setglobal(L,"unitData");

    luaL_dostring(L, "print(\"unitData.hurtVar\")");
    luaL_dostring(L, "print(unitData.hurtVar)");
}

void UIManager::setMovementList()
{
    LuaEngine *pEngine = LuaEngine::getInstance();
    lua_State *L = pEngine->getLuaStack()->getLuaState();

    lua_newtable(L);
    lua_pushstring(L,"attack");

        lua_newtable(L);

        lua_pushstring(L,"category");
        lua_pushliteral(L,"attack");
        lua_settable(L,-3);

        lua_pushstring(L,"aim");
        lua_pushnumber(L,3);
        lua_settable(L,-3);

    lua_settable(L,-3);

    lua_pushstring(L,"skill_U");
        lua_newtable(L);

        lua_pushstring(L,"category");
        lua_pushliteral(L,"skill");
        lua_settable(L,-3);

        lua_pushstring(L,"aim");
        lua_pushnumber(L,4);
        lua_settable(L,-3);

    lua_settable(L,-3);

    lua_pushstring(L,"skill_I");
    lua_newtable(L);

        lua_pushstring(L,"category");
        lua_pushliteral(L,"skill");
        lua_settable(L,-3);

        lua_pushstring(L,"aim");
        lua_pushnumber(L,5);
        lua_settable(L,-3);

    lua_settable(L,-3);

    lua_pushstring(L,"skill_O");
    lua_newtable(L);

        lua_pushstring(L,"category");
        lua_pushliteral(L,"skill");
        lua_settable(L,-3);

        lua_pushstring(L,"aim");
        lua_pushnumber(L,6);
        lua_settable(L,-3);

    lua_settable(L,-3);

    lua_pushstring(L,"skill_L");
    lua_newtable(L);
        lua_pushstring(L,"category");
        lua_pushliteral(L,"skill");
        lua_settable(L,-3);

        lua_pushstring(L,"aim");
        lua_pushnumber(L,7);
        lua_settable(L,-3);
    lua_settable(L,-3);

    lua_pushstring(L,"skill_H");
    lua_newtable(L);

        lua_pushstring(L,"category");
        lua_pushliteral(L,"skill");
        lua_settable(L,-3);

        lua_pushstring(L,"aim");
        lua_pushnumber(L,8);
        lua_settable(L,-3);

    lua_settable(L,-3);

    lua_setglobal(L,"movementList");

}

const char* getStringByKey(Dictionary *dic, const char* key)
{
    if (key && dic)
    {
        String *str = dynamic_cast<String*>(dic->objectForKey(key));
        if (str)
        {
            return str->getCString();
        }
    }

    return "";
}

int getIntByKey(Dictionary *dic, const char* key)
{
    if (key && dic)
    {
        String *str = dynamic_cast<String*>(dic->objectForKey(key));
        if (str)
        {
           return str->intValue();
        }
    }

    return 0;
}

/**
 *
            skillname = "warrior attack 1",
            category = "attack",
            hurtMotion = 0,

            hurtStiffTime = 1,
            hurtMovingTime = 0.3,
            bSpeedValue = 180,

            float = 0,
            height = 180

 **/

void UIManager::setSkillDataItem(String *key, Dictionary *dic)
{
    lua_newtable(L);
    lua_pushstring(L,key->getCString());

    lua_pushstring(L,"skillname");
    lua_pushstring(L, getStringByKey(dic,"skillname"));
    lua_settable(L,-3);

    lua_pushstring(L,"category");
    lua_pushstring(L, getStringByKey(dic,"attack"));
    lua_settable(L,-3);

    lua_pushstring(L,"hurtMotion");
    lua_pushnumber(L, getIntByKey(dic,"hurtMotion"));
    lua_settable(L,-3);

    lua_pushstring(L,"hurtStiffTime");
    lua_pushnumber(L, getIntByKey(dic,"hurtStiffTime"));
    lua_settable(L,-3);

    lua_pushstring(L,"hurtMovingTime");
    lua_pushnumber(L, getIntByKey(dic,"hurtMovingTime"));
    lua_settable(L,-3);

    lua_pushstring(L,"bSpeedValue");
    lua_pushnumber(L, getIntByKey(dic,"bSpeedValue"));
    lua_settable(L,-3);

    lua_pushstring(L,"beatFlip");
    lua_pushnumber(L, getIntByKey(dic,"beatFlip"));
    lua_settable(L,-3);

    lua_pushstring(L,"float");
    lua_pushnumber(L, getIntByKey(dic,"float"));
    lua_settable(L,-3);

    lua_pushstring(L,"height");
    lua_pushnumber(L, getIntByKey(dic,"height"));
    lua_settable(L,-3);

    lua_pushstring(L,"beatfloat");
    lua_pushnumber(L, getIntByKey(dic,"beatfloat"));
    lua_settable(L,-3);

    lua_pushstring(L,"beatfloatDuration");
    lua_pushnumber(L, getIntByKey(dic,"beatfloatDuration"));
    lua_settable(L,-3);

    lua_settable(L,-3);

}

void UIManager::setSkillData()
{
    lua_newtable(L);

//    String* key = "attack_4";
//    Dictionary *dic = new Dictionary();
//    dic->setObject(StringMake("attack1"),"skillname");
//    dic->setObject(StringMake("skill"),"category");
//    dic->setObject(StringMake("1"),"hurtMotion");
//    dic->setObject(StringMake("1"),"hurtMotion");

//    lua_pushstring(L,"hurtStiffTime");

//    lua_pushstring(L,"hurtMovingTime");

//    lua_pushstring(L,"bSpeedValue");

//    lua_pushstring(L,"beatFlip");

//    lua_pushstring(L,"float");

//    lua_pushstring(L,"height");

//    lua_pushstring(L,"beatfloat");

//    lua_pushstring(L,"beatfloatDuration");
//    setSkillDataItem(key,dic);

//    delete dic;
//    dic = NULL;

//    lua_setglobal(L,"unitData");
//    luaL_dostring(L, "print(\"unitData.hurtVar\")");
//    luaL_dostring(L, "print(unitData.hurtVar)");
}



