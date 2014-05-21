#include "src/MainWindow.h"
#include "ui_MainWindow.h"
#include "cocos2d.h"
#include <QFileDialog>
#include "luabridge.h"

USING_NS_CC;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

QWidget*
MainWindow::getGLViewSuperWidget()
{
    return ui->widget;
}

void MainWindow::on_pushButton_clicked()
{
    CCLOG(" HELLO ");
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "/Users/fight ", tr("Image Files (*.* *.jpg )"));
    CCLOG("%s",fileName.toStdString().c_str());

    LuaBridge::getInstance()->setPath(fileName.toStdString());
}
