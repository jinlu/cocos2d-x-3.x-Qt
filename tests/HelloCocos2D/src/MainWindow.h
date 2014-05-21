#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#if QT_VERSION >= 0x050000
//#include <QtWidgets/QMainWindow>
//#else
#include <QMainWindow>
//#endif

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

//private slots:
public Q_SLOTS:
    void on_pushButton_clicked();

private Q_SLOTS:

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
