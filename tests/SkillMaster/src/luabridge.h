#ifndef LUABRIDGE_H
#define LUABRIDGE_H

#include "iostream"
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class LuaBridge : public Object
{

private:
    string path;

public:
    LuaBridge();
    static LuaBridge* getInstance();
    void setPath(string str);
    const char* getPath();

};

#endif // LUABRIDGE_H
