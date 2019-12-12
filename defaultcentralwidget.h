#ifndef DEFAULTCENTRALWIDGET_H
#define DEFAULTCENTRALWIDGET_H

#include <QWidget>
#include <QMainWindow>

class DefaultCentralWidget : public QWidget
{
    Q_OBJECT
public:
    DefaultCentralWidget(QMainWindow *mainWindow,QWidget *parent = 0);
    ~DefaultCentralWidget();
};

#endif // DEFAULTCENTRALWIDGET_H
