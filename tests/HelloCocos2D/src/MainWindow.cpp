#include "src/MainWindow.h"
#include "ui_MainWindow.h"
#include "cocos2d.h"
#include <QFileDialog>
#include "luabridge.h"
#include "CCLuaEngine.h"
#include "CCEventCustom.h"
#include "UIManager.h"
#include <QDebug>
#include "stdio.h"
#include "lua2c.h"

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
    lua_State *L = pEngine->getLuaStack()->getLuaState();
    manager = new UIManager(this,L);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
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

void MainWindow::print()
{
//    manager->setUnitData();
//    luaL_dostring(L, "print(movementList.skill_H.category)");
//    luaL_dostring(L, "print(movementList.skill_H.aim)");
    manager->setUnitData();
}

void MainWindow::load()
{
  qDebug() << "MainWindow:load";

  LuaEngine *pEngine = LuaEngine::getInstance();
  lua_State *L = pEngine->getLuaStack()->getLuaState();

  QTabWidget *tabWidget = this->findChild<QTabWidget *>(tr("tabWidget"));

  // load unitdata
  QWidget * tab1 = tabWidget->findChild<QWidget*>(tr("tab_1"));
  QWidget * tab1_group = tab1->findChild<QWidget*>(tr("groupBox"));
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

  QWidget * tab2 = tabWidget->findChild<QWidget*>(tr("tab_2"));
  QWidget * tab2_group = tab2->findChild<QWidget*>(tr("groupBox_2"));
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
//                  qDebug() << code;
                  lineEdit1->setText(Lua2C::getStringValue(L,code.toStdString().c_str()));
              }
          }
      }
  }
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
//    qDebug() << label->text();
    return label->text();
}
