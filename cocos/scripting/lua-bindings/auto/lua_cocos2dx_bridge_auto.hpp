#ifndef __cocos2dx_bridge_h__
#define __cocos2dx_bridge_h__

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

int register_all_cocos2dx_bridge(lua_State* tolua_S);




#endif // __cocos2dx_bridge_h__
