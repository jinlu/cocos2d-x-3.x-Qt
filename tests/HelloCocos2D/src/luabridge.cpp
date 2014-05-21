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
//    qDebug() << "LuaBridge::setPath : " << string;
    CCLOG("LuaBridge::setPath :  %s ", str.c_str());
    path = str;
}

const char* LuaBridge::getPath()
{
//    qDebug() << "LuaBridge::getPath : " << path;
    return path.c_str();
}

