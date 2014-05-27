#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "cocos2d.h"

USING_NS_CC;

class MainWindow;

struct UnitDataTable {
  char *name;
  int speed;
  int discoverRadii;
  int discoverOffset;
  int hurtBasePoint;
  int hurtVar;
};

extern UnitDataTable UnitData[];

class UIManager
{
public:
    UIManager(MainWindow *mw, lua_State *state);

    void setUnitData();
    void getUnitData(struct UnitDataTable& table);
    void setMovementList();
    void setSkillData();
    void setSkillDataItem(String *key, Dictionary *dic);

private:
    MainWindow *mainWindow;
    lua_State  *L;

};

#endif // UIMANAGER_H
