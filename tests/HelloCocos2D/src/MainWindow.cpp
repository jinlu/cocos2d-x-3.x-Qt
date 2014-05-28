#include <QFileDialog>
#include <QDebug>
#include "src/MainWindow.h"
#include "ui_MainWindow.h"
#include "cocos2d.h"
#include "luabridge.h"
#include "CCEventCustom.h"
#include "stdio.h"
#include "lua2c.h"
#include "lua_extensions.h"

USING_NS_CC;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStackedWidget *stackedWidget = this->findChild<QStackedWidget *>(tr("stackedWidget"));
    if (stackedWidget)
    {
        stackedWidget->setCurrentIndex(0);
    }

    LuaEngine *pEngine = LuaEngine::getInstance();
    L = pEngine->getLuaStack()->getLuaState();

    setValidator();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::load()
{
  qDebug() << "MainWindow:load";

  LuaEngine *pEngine = LuaEngine::getInstance();
  lua_State *L = pEngine->getLuaStack()->getLuaState();

  QTabWidget *tabWidget = this->findChild<QTabWidget *>(tr("tabWidget"));

  // load unitdata
  QWidget *tab1 = tabWidget->findChild<QWidget*>(tr("tab_1"));
  QWidget *tab1_group = tab1->findChild<QWidget*>(tr("groupBox"));
  if (tab1_group)
  {
      QLineEdit *edit1 = tab1_group->findChild<QLineEdit*>(tr("lineEdit"));
      QLineEdit *edit2 = tab1_group->findChild<QLineEdit*>(tr("lineEdit_2"));
      QLineEdit *edit3 = tab1_group->findChild<QLineEdit*>(tr("lineEdit_3"));
      QLineEdit *edit4 = tab1_group->findChild<QLineEdit*>(tr("lineEdit_4"));
      QLineEdit *edit5 = tab1_group->findChild<QLineEdit*>(tr("lineEdit_5"));

      edit1->setText(Lua2C::getStringValue(L,"global_config.unitData.speed"));
      edit2->setText(Lua2C::getStringValue(L,"global_config.unitData.discoverRadii"));
      edit3->setText(Lua2C::getStringValue(L,"global_config.unitData.discoverOffset"));
      edit4->setText(Lua2C::getStringValue(L,"global_config.unitData.hurtBasePoint"));
      edit5->setText(Lua2C::getStringValue(L,"global_config.unitData.hurtVar"));
  }

  // load movementList
  QWidget *tab2 = tabWidget->findChild<QWidget*>(tr("tab_2"));
  QWidget *tab2_group = tab2->findChild<QWidget*>(tr("groupBox_2"));
  if (tab2_group)
  {
      QLineEdit *edit1 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_1"));
      QLineEdit *edit2 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_2"));
      QLineEdit *edit3 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_3"));
      QLineEdit *edit4 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_4"));
      QLineEdit *edit5 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_5"));
      QLineEdit *edit6 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_6"));
      QLineEdit *edit7 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_7"));
      QLineEdit *edit8 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_8"));
      QLineEdit *edit9 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_9"));
      QLineEdit *edit10 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_10"));
      QLineEdit *edit11 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_11"));
      QLineEdit *edit12 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_12"));

      edit1->setText(Lua2C::getStringValue(L,"global_config.movementList.attack.category"));
      edit2->setText(Lua2C::getStringValue(L,"global_config.movementList.attack.aim"));
      edit3->setText(Lua2C::getStringValue(L,"global_config.movementList.skill_U.category"));
      edit4->setText(Lua2C::getStringValue(L,"global_config.movementList.skill_U.aim"));
      edit5->setText(Lua2C::getStringValue(L,"global_config.movementList.skill_I.category"));
      edit6->setText(Lua2C::getStringValue(L,"global_config.movementList.skill_I.aim"));
      edit7->setText(Lua2C::getStringValue(L,"global_config.movementList.skill_O.category"));
      edit8->setText(Lua2C::getStringValue(L,"global_config.movementList.skill_O.aim"));
      edit9->setText(Lua2C::getStringValue(L,"global_config.movementList.skill_L.category"));
      edit10->setText(Lua2C::getStringValue(L,"global_config.movementList.skill_L.aim"));
      edit11->setText(Lua2C::getStringValue(L,"global_config.movementList.skill_H.category"));
      edit12->setText(Lua2C::getStringValue(L,"global_config.movementList.skill_H.aim"));
  }

  // load skillData
  QWidget *tab3 = tabWidget->findChild<QWidget*>(tr("tab_3"));
  QWidget *root = tab3->findChild<QWidget*>(tr("root"));

  if (root)
  {
      for (int i = 0; i < 13; i++)
      {
          QString groupName = QString("group%1")
                                      .arg(i + 1);
          QList<QGroupBox*> list = root->findChildren<QGroupBox*>(groupName);

          if (list.count() <= 0)
          {
              break;
          }

          QGroupBox *group = list.at(0);
          if (group == NULL)
          {
              break;
          }

          for (int j = 0; j < 13; j++)
          {
              QString string = QString("lineEdit_%1_%2")
                          .arg(i + 1)
                          .arg(j);
              QLineEdit *lineEdit1 = group->findChild<QLineEdit*>(string);
              if (lineEdit1)
              {
                  QString code = QString("global_config.skillData.%1.%2")
                          .arg(getSkillActionName(i))
                          .arg(getSkillKeyName(j));
                  lineEdit1->setText(Lua2C::getStringValue(L,code.toStdString().c_str()));
              }
          }
      }
  }
}

void MainWindow::save()
{
    lua_newtable(L);

    lua_pushstring(L, "unitData");
    setUnitData();
    lua_settable(L,-3);

    lua_pushstring(L, "movementList");
    setMovementList();
    lua_settable(L,-3);

    lua_pushstring(L, "skillData");
    setSkillData();
    lua_settable(L,-3);

    lua_setglobal(L,"tmpConfig");

    luaL_dostring(L, "print(\"tmpConfig.skillData.flamingChariot.skillname\")");
    luaL_dostring(L, "print(tmpConfig.skillData.flamingChariot.skillname)");

    luaL_dostring(L, "file = io.open('../Resources/tmpConfig.lua','w')");
    luaL_dostring(L, "persistence.store(file,tmpConfig)");
    luaL_dostring(L, "print(\" save succeed! \")");
}

QWidget* MainWindow::getGLViewSuperWidget()
{
    return ui->widget;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "/Users/fight ", tr("Image Files (*.ExportJson)"));

    LuaBridge::getInstance()->setPath(fileName.toStdString());

    auto scene = Director::getInstance()->getRunningScene();
    auto eventDispatcher = scene->getEventDispatcher();
    EventCustom event("EVENT_TEST");
    eventDispatcher->dispatchEvent(&event);

}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
//    qDebug() << "Combo Index : " << index;

    QStackedWidget *stackedWidget = this->findChild<QStackedWidget *>(tr("stackedWidget"));
    if (index >= 0 && index < stackedWidget->count())
    {
        stackedWidget->setCurrentIndex(index);
    }

}

// index 0-13
QString MainWindow::getSkillActionName(int index)
{
    if (index < 0 || index > 13)
    {
        return QString("");
    }

    QComboBox *combox = this->findChildren<QComboBox*>("comboBox")[0];
    if (combox == NULL)
    {
        return QString("");
    }

    return combox->itemText(index);
}

// index 0-11
QString MainWindow::getSkillKeyName(int index)
{
    if (index < 0 || index > 13)
    {
        return QString("");
    }

    QList<QLabel*> list = this->findChildren<QLabel*>(QString("name_%1").arg(index + 1));
    if (list.count() <= 0)
    {
        return QString("");
    }

    QLabel *label = list.at(0);
    return label->text();
}

void MainWindow::setUnitData()
{
//    mainWindow
    QTabWidget *tabWidget = this->findChild<QTabWidget *>(tr("tabWidget"));
    QWidget *tab1 = tabWidget->findChild<QWidget*>(tr("tab_1"));
    QWidget *tab1_group = tab1->findChild<QWidget*>(tr("groupBox"));

    if (tab1_group)
    {
        QLineEdit *edit1 = tab1_group->findChild<QLineEdit*>(tr("lineEdit"));
        QLineEdit *edit2 = tab1_group->findChild<QLineEdit*>(tr("lineEdit_2"));
        QLineEdit *edit3 = tab1_group->findChild<QLineEdit*>(tr("lineEdit_3"));
        QLineEdit *edit4 = tab1_group->findChild<QLineEdit*>(tr("lineEdit_4"));
        QLineEdit *edit5 = tab1_group->findChild<QLineEdit*>(tr("lineEdit_5"));

        lua_newtable(L);

        lua_pushstring(L,"speed");
        lua_pushnumber(L,edit1->text().toInt());
        lua_settable(L,-3);

        lua_pushstring(L,"discoverRadii");
        lua_pushnumber(L,edit2->text().toInt());
        lua_settable(L,-3);

        lua_pushstring(L,"discoverOffset");
        lua_pushnumber(L,edit3->text().toInt());
        lua_settable(L,-3);

        lua_pushstring(L,"hurtBasePoint");
        lua_pushnumber(L,edit4->text().toInt());
        lua_settable(L,-3);

        lua_pushstring(L,"hurtVar");
        lua_pushnumber(L,edit5->text().toInt());
        lua_settable(L,-3);

//        qDebug() << "5 : " << edit5->text();

//        lua_setglobal(L,"unitData");
//        luaL_dostring(L, "print(-->unitData)");
//        luaL_dostring(L, "print(unitData.speed)");
//        luaL_dostring(L, "print(unitData.discoverRadii)");
//        luaL_dostring(L, "print(unitData.discoverOffset)");
//        luaL_dostring(L, "print(unitData.hurtBasePoint)");
//        luaL_dostring(L, "print(unitData.hurtVar)");
    }
}

/*
category = "attack",
aim = 3
 */
void MainWindow::setMovementItem(const char* category, int aim)
{
    lua_newtable(L);

    lua_pushstring(L,"category");
    lua_pushstring(L,category);
    lua_settable(L,-3);

    lua_pushstring(L,"aim");
    lua_pushnumber(L,aim);
    lua_settable(L,-3);    
}

void MainWindow::setMovementList()
{
    QTabWidget *tabWidget = this->findChild<QTabWidget *>(tr("tabWidget"));
    QWidget *tab2 = tabWidget->findChild<QWidget*>(tr("tab_2"));
    QWidget *tab2_group = tab2->findChild<QWidget*>(tr("groupBox_2"));

    if (tab2_group)
    {
        QLineEdit *edit1 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_1"));
        QLineEdit *edit2 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_2"));
        QLineEdit *edit3 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_3"));
        QLineEdit *edit4 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_4"));
        QLineEdit *edit5 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_5"));
        QLineEdit *edit6 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_6"));
        QLineEdit *edit7 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_7"));
        QLineEdit *edit8 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_8"));
        QLineEdit *edit9 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_9"));
        QLineEdit *edit10 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_10"));
        QLineEdit *edit11 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_11"));
        QLineEdit *edit12 = tab2_group->findChild<QLineEdit*>(tr("lineEdit2_12"));

        lua_newtable(L);

        /*
         * attack = {
            category = "attack",
            aim = 3
           },
         */
        lua_pushstring(L,"attack");
        setMovementItem(edit1->text().toStdString().c_str(),edit2->text().toInt());
        lua_settable(L,-3);

        lua_pushstring(L,"skill_U");
        setMovementItem(edit3->text().toStdString().c_str(),edit4->text().toInt());
        lua_settable(L,-3);

        lua_pushstring(L,"skill_I");
        setMovementItem(edit5->text().toStdString().c_str(),edit6->text().toInt());
        lua_settable(L,-3);

        lua_pushstring(L,"skill_O");
        setMovementItem(edit7->text().toStdString().c_str(),edit8->text().toInt());
        lua_settable(L,-3);

        lua_pushstring(L,"skill_L");
        setMovementItem(edit9->text().toStdString().c_str(),edit10->text().toInt());
        lua_settable(L,-3);

        lua_pushstring(L,"skill_H");
        setMovementItem(edit11->text().toStdString().c_str(),edit12->text().toInt());
        lua_settable(L,-3);

//        lua_setglobal(L,"movementList");

//        luaL_dostring(L, "print(\"-->movementList\")");
//        luaL_dostring(L, "print(movementList.attack.category)");
//        luaL_dostring(L, "print(movementList.attack.aim)");
//        luaL_dostring(L, "print(movementList.skill_U.category)");
//        luaL_dostring(L, "print(movementList.skill_U.aim)");
//        luaL_dostring(L, "print(movementList.skill_I.category)");
//        luaL_dostring(L, "print(movementList.skill_I.aim)");
//        luaL_dostring(L, "print(movementList.skill_O.category)");
//        luaL_dostring(L, "print(movementList.skill_O.aim)");
//        luaL_dostring(L, "print(movementList.skill_L.category)");
//        luaL_dostring(L, "print(movementList.skill_L.aim)");
//        luaL_dostring(L, "print(movementList.skill_H.category)");
//        luaL_dostring(L, "print(movementList.skill_H.aim)");
    }
}

void MainWindow::setSkillData()
{
    QTabWidget *tabWidget = this->findChild<QTabWidget *>(tr("tabWidget"));
    QWidget *tab3 = tabWidget->findChild<QWidget*>(tr("tab_3"));
    QWidget *root = tab3->findChild<QWidget*>(tr("root"));

    if (root)
    {
        lua_newtable(L);

        for (int i = 0; i < 13; i++)
        {
            QString groupName = QString("group%1")
                                        .arg(i + 1);
            QList<QGroupBox*> list = root->findChildren<QGroupBox*>(groupName);

            if (list.count() <= 0)
            {
                break;
            }

            QGroupBox *group = list.at(0);
            if (group == NULL)
            {
                break;
            }

            lua_pushstring(L, getSkillActionName(i).toStdString().c_str());
            lua_newtable(L);


            for (int j = 0; j < 2; j++)
            {
                // combo 1
                QString string = QString("comboBox_%1_%2")
                            .arg(i + 1)
                            .arg(j + 1);
                QComboBox *comboBox = group->findChild<QComboBox*>(string);
                if (comboBox)
                {
                    if (j == 0)
                    {
                        lua_pushstring(L, "category");
                        lua_pushstring(L, comboBox->currentText().toStdString().c_str());
                        lua_settable(L,-3);
                    }
                    else if(j == 1)
                    {
                        bool value = (QString::compare(comboBox->currentText(),"true",Qt::CaseSensitive) == 0);
                        lua_pushstring(L, "beatFlip");
                        lua_pushboolean(L, value);
                        lua_settable(L,-3);
                    }
                }
            }

            // line Edit
            for (int j = 0; j < 13; j++)
            {
                QString string = QString("lineEdit_%1_%2")
                            .arg(i + 1)
                            .arg(j);
                QLineEdit *lineEdit1 = group->findChild<QLineEdit*>(string);
                if (lineEdit1)
                {
                    const QIntValidator* validator = dynamic_cast<const QIntValidator*>(lineEdit1->validator());
                    if (validator)
                    {
//                        qDebug() << "number : " << lineEdit1->text().toFloat();
                        lua_pushstring(L, getSkillKeyName(j).toStdString().c_str());
                        lua_pushnumber(L, lineEdit1->text().toDouble());
                        lua_settable(L,-3);
                    }
                    else
                    {
//                        qDebug() << "text : " << lineEdit1->text();
                        lua_pushstring(L, getSkillKeyName(j).toStdString().c_str());
                        lua_pushstring(L, lineEdit1->text().toStdString().c_str());
                        lua_settable(L,-3);
                    }

                }
             }

            lua_settable(L,-3);
        }
    }

//    lua_setglobal(L,"skillData");

//    luaL_dostring(L, "print(\"-->skillData\")");
//    luaL_dostring(L, "print(skillData.attack_1.skillname)");
//    luaL_dostring(L, "print(skillData.attack_1.category)");
//    luaL_dostring(L, "print(skillData.attack_1.hurtMotion)");
//    luaL_dostring(L, "print(skillData.attack_1.hurtStiffTime)");
//    luaL_dostring(L, "print(skillData.attack_1.hurtMovingTime)");
//    luaL_dostring(L, "print(skillData.attack_1.bSpeedValue)");
//    luaL_dostring(L, "print(skillData.attack_1.beatFlip)");
//    luaL_dostring(L, "print(skillData.attack_1.float)");
//    luaL_dostring(L, "print(skillData.attack_1.height)");
//    luaL_dostring(L, "print(skillData.attack_1.beatFloat)");
//    luaL_dostring(L, "print(skillData.attack_1.beatFloatDuration)");
//    luaL_dostring(L, "print(skillData.attack_1.hurtEffect)");
//    luaL_dostring(L, "print(skillData.attack_1.loops)");
}

void MainWindow::setValidator()
{
    QTabWidget *tabWidget = this->findChild<QTabWidget *>(tr("tabWidget"));
    QWidget *tab3 = tabWidget->findChild<QWidget*>(tr("tab_3"));
    QWidget *root = tab3->findChild<QWidget*>(tr("root"));

    if (root)
    {
        for (int i = 0; i < 13; i++)
        {
            QString groupName = QString("group%1")
                                        .arg(i + 1);
            QList<QGroupBox*> list = root->findChildren<QGroupBox*>(groupName);

            if (list.count() <= 0)
            {
                break;
            }

            QGroupBox *group = list.at(0);
            if (group == NULL)
            {
                break;
            }

            for (int j = 0; j < 13; j++)
            {
                QString string = QString("lineEdit_%1_%2")
                            .arg(i + 1)
                            .arg(j);
                QLineEdit *lineEdit1 = group->findChild<QLineEdit*>(string);
                if (lineEdit1)
                {
                    switch (j)
                    {
                        // skillname
                        case 0:
                            break;
                        // category
                        case 1:
                            break;
                        // hurtMotion
                        case 2:
                        {
                            QValidator *validator = new QIntValidator(0, 999999, this);
                            lineEdit1->setValidator(validator);
                        }
                            break;
                        // hurtStiffTime
                        case 3:
                        {
                            QValidator *validator = new QIntValidator(0, 999999, this);
                            lineEdit1->setValidator(validator);
                        }
                            break;
                        // hurtMovingTime
                        case 4:
                        {
                            QValidator *validator = new QIntValidator(0, 999999, this);
                            lineEdit1->setValidator(validator);
                        }
                            break;
                        // bSpeedValue
                        case 5:
                        {
                            QValidator *validator = new QIntValidator(0, 999999, this);
                            lineEdit1->setValidator(validator);
                        }
                            break;
                        // beatFlip
                        case 6:
                            break;
                        // float
                        case 7:
                        {
                            QValidator *validator = new QIntValidator(0, 999999, this);
                            lineEdit1->setValidator(validator);
                        }
                            break;
                        // height
                        case 8:
                        {
                            QValidator *validator = new QIntValidator(0, 999999, this);
                            lineEdit1->setValidator(validator);
                        }
                            break;
                        // beatFloat
                        case 9:
                        {
                            QValidator *validator = new QIntValidator(0, 999999, this);
                            lineEdit1->setValidator(validator);
                        }
                            break;
                        // beatFloatDuration
                        case 10:
                        {
                            QValidator *validator = new QIntValidator(0, 999999, this);
                            lineEdit1->setValidator(validator);
                        }
                            break;
                        // hurtEffect
                        case 11:
                            break;
                        // loops
                        case 12:
                        {
                            QValidator *validator = new QIntValidator(0, 999999, this);
                            lineEdit1->setValidator(validator);
                        }
                            break;
                    default:
                        break;
                    }
                }
             }
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    save();
}
