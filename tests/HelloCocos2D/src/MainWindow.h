#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CCLuaEngine.h"

//#if QT_VERSION >= 0x050000
//#include <QtWidgets/QMainWindow>
//#else
#include <QMainWindow>4ewee3w3cwc3skmiu treh
//#endif

class UIManager;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

public:
    QWidget* getGLViewSuperWidget(void);
    void load();
    void save();

//private slots:
private Q_SLOTS:

    void on_actionOpen_triggered();
    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    // index 0-13
    QString getSkillActionName(int index);

    // index 0-11
    QString getSkillKeyName(int index);

    // data
    void setUnitData();
    void setMovementItem(const char* category, int aim);
    void setMovementList();
    void setSkillData();

    // other
    void setValidator();

    lua_State *L;
};

#endif // MAINWINDOW_H
