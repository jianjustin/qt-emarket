#ifndef ADDCOMMODITYWIDGET_H
#define ADDCOMMODITYWIDGET_H

#include <QWidget>
#include <QMainWindow>

class AddCommodityWidget : public QWidget
{
    Q_OBJECT
public:
    AddCommodityWidget(QMainWindow *mainWindow,QWidget *parent = 0);
    ~AddCommodityWidget();
};

#endif // ADDCOMMODITYWIDGET_H
