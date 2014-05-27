#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//#include "uimanager.h"

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
    void print();
    void load();

//private slots:
private Q_SLOTS:

    void on_actionOpen_triggered();
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    UIManager      *manager;

    // index 0-13
    QString getSkillActionName(int index);

    // index 0-11
    QString getSkillKeyName(int index);
};

#endif // MAINWINDOW_H
