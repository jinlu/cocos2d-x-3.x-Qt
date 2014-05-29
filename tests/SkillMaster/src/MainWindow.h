#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CCLuaEngine.h"
#include "qcombobox.h"
#include <QMainWindow>

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

    void on_lineEdit_1_0_textEdited(const QString &arg1);

    void on_comboBox_1_1_currentTextChanged(const QString &arg1);

    void on_lineEdit_1_2_textEdited(const QString &arg1);

    void on_lineEdit_1_3_textEdited(const QString &arg1);

    void on_lineEdit_1_4_textEdited(const QString &arg1);

    void on_lineEdit_1_5_textEdited(const QString &arg1);

    void on_comboBox_1_2_currentTextChanged(const QString &arg1);

    void on_lineEdit_1_7_textEdited(const QString &arg1);

    void on_lineEdit_1_8_textEdited(const QString &arg1);

    void on_lineEdit_1_9_textEdited(const QString &arg1);

    void on_lineEdit_1_10_textEdited(const QString &arg1);

    void on_lineEdit_1_11_textEdited(const QString &arg1);

    void on_lineEdit_1_12_textEdited(const QString &arg1);

    void on_actionReload_triggered();

private:
    Ui::MainWindow *ui;

    // index 0-11
    QString getSkillKeyName(int index);

    // load data
    void loadSkillData();

    // save data
    void setUnitData();
    void setMovementItem(const char* category, const char* aim);
    void setMovementList();
    void setSkillData();    

    // other
    void setValidator();

    void setComboText(QComboBox* comboBox,QString text);        

    lua_State *L;
    QTabWidget* tabWidget;
};

double getPointX(QString str);
double getPointY(QString str);
void lua_pushPoint(lua_State*L, double x, double y);
QString getFileName(QString path);

#endif // MAINWINDOW_H
