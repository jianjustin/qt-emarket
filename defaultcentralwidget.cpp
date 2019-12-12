#include "defaultcentralwidget.h"

DefaultCentralWidget::DefaultCentralWidget(QMainWindow *mainWindow,QWidget *parent) : QWidget(parent)
{
    mainWindow->setWindowTitle("e电子商城系统 - 主页");
    this->setFixedSize(720,540);
}

DefaultCentralWidget::~DefaultCentralWidget()
{

}
