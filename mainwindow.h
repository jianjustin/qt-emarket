#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QGridLayout>
#include <QPushButton>

#include "defaultcentralwidget.h"
#include "commoditylistwidget.h"
#include "addcommoditywidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    void createMenus();
    void createActions();
    ~MainWindow();
private slots:
    void showCommodityListPage();
    void addCommodity();
private:
    QAction *showGoodsAction;
    QAction *addGoodsAction;
    QAction *logoutAction;
    QMenu *goodsMenu;
    QMenu *systemMenu;

    //UI widgets
    DefaultCentralWidget *centralWidget;//主页面，默认
    CommodityListWidget *commodityListWidget;//商品列表widget
    AddCommodityWidget *addCommodityWidget;//添加商品widget
};

#endif // MAINWINDOW_H
