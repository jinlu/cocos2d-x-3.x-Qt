//#include "uimanager.h"
//#include "CCLuaEngine.h"
//#include "lua_extensions.h"
//#include <QMainWindow>

//UnitDataTable UnitData[] = {
//  {"speed",   1, },
//  {"discoverRadii",     1,},
//  {"discoverOffset",   0, },
//  {"hurtBasePoint",    0, },
//  {"hurtVar",      0, }  /* sentinel */
//};





//const char* getStringByKey(Dictionary *dic, const char* key)
//{
//    if (key && dic)
//    {
//        String *str = dynamic_cast<String*>(dic->objectForKey(key));
//        if (str)
//        {
//            return str->getCString();
//        }
//    }

//    return "";
//}

//int getIntByKey(Dictionary *dic, const char* key)
//{
//    if (key && dic)
//    {
//        String *str = dynamic_cast<String*>(dic->objectForKey(key));
//        if (str)
//        {
//           return str->intValue();
//        }
//    }

//    return 0;
//}

///**
// *
//            skillname = "warrior attack 1",
//            category = "attack",
//            hurtMotion = 0,

//            hurtStiffTime = 1,
//            hurtMovingTime = 0.3,
//            bSpeedValue = 180,

//            float = 0,
//            height = 180

// **/

//void UIManager::setSkillDataItem(String *key, Dictionary *dic)
//{


//}

//void UIManager::setSkillData()
//{
//    lua_newtable(L);

////    String* key = "attack_4";
////    Dictionary *dic = new Dictionary();
////    dic->setObject(StringMake("attack1"),"skillname");
////    dic->setObject(StringMake("skill"),"category");
////    dic->setObject(StringMake("1"),"hurtMotion");
////    dic->setObject(StringMake("1"),"hurtMotion");

////    lua_pushstring(L,"hurtStiffTime");

////    lua_pushstring(L,"hurtMovingTime");

////    lua_pushstring(L,"bSpeedValue");

////    lua_pushstring(L,"beatFlip");

////    lua_pushstring(L,"float");

////    lua_pushstring(L,"height");

////    lua_pushstring(L,"beatfloat");

////    lua_pushstring(L,"beatfloatDuration");
////    setSkillDataItem(key,dic);

////    delete dic;
////    dic = NULL;

////    lua_setglobal(L,"unitData");
////    luaL_dostring(L, "print(\"unitData.hurtVar\")");
////    luaL_dostring(L, "print(unitData.hurtVar)");
//}



