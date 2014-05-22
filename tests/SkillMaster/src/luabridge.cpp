#include "luabridge.h"
#include "cocos2d.h"

static LuaBridge *_luaBridge = nullptr;

LuaBridge::LuaBridge()
{
    path = "default path";
}

LuaBridge* LuaBridge::getInstance()
{
    if (_luaBridge == nullptr)
    {
        _luaBridge = new LuaBridge();
    }

    return _luaBridge;
}

void LuaBridge::setPath(string str)
{
    path = str;
    CCLOG("LuaBridge::setPath :  %s :  %lld ", path.c_str(), (long long)this);
}

const char* LuaBridge::getPath()
{
    CCLOG("LuaBridge::getPath :  %s : %lld ", path.c_str(), (long long )this);
    return path.c_str();
}

