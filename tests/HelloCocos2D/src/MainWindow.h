#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CCLuaEngine.h"
#include "qcombobox.h"

//#if QT_VERSION >= 0x050000
//#include <QtWidgets/QMainWindow>
//#else
#include <QMainWindow>
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
    void prepareLua();
    void load();
    void save(const char* path = NULL);

//private slots:
private Q_SLOTS:

    void on_actionOpen_triggered();
    void on_comboBox_currentIndexChanged(int index);
    void on_actionSave_triggered();

    void on_actionSave_AS_triggered();

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

    void setComboText(QComboBox* comboBox,QString text);
    lua_State *L;
};

#endif // MAINWINDOW_H
