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
#include "orderlistwidget.h"

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
    void showOrdersListPage();
private:
    QAction *showGoodsAction;
    QAction *ordersAction;
    QAction *logoutAction;
    QMenu *goodsMenu;
    QMenu *systemMenu;

    //UI widgets
    DefaultCentralWidget *centralWidget;//主页面，默认
    CommodityListWidget *commodityListWidget;//商品列表widget
    OrderListWidget *orderListWidget;//订单列表widget
};

#endif // MAINWINDOW_H
