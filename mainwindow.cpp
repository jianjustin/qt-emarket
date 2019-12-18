#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("e电子商城系统");
    this->setStyleSheet("QMainWindow {background-image:url(/Users/jian/workspace/qt-emarket/images/default.png)}");//设置背景图片
    this->setFixedSize(800,600);
    createActions();
    createMenus();

    //默认主页，参考"defaultcentralwidget"
    centralWidget = new DefaultCentralWidget(this);
    this->setCentralWidget(centralWidget);

}


MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
    showGoodsAction = new QAction("商品",this);
    connect(showGoodsAction,SIGNAL(triggered()),this,SLOT (showCommodityListPage()));
    ordersAction =new QAction("订单",this);
    connect(ordersAction,SIGNAL(triggered()),this,SLOT (showOrdersListPage()));
    logoutAction = new QAction("登出",this);
}

void MainWindow::createMenus(){
    goodsMenu = menuBar()->addMenu("功能");
    goodsMenu->addAction(showGoodsAction);
    goodsMenu->addAction(ordersAction);
    systemMenu = menuBar()->addMenu("系统");
    systemMenu->addAction(logoutAction);
}

/**
 * 进入商品模块
 */
void MainWindow::showCommodityListPage(){
    commodityListWidget = new CommodityListWidget(this);
    this->centralWidget->setParent(0);
    this->setCentralWidget(commodityListWidget);
}

/**
 * 进入订单模块
 */
void MainWindow::showOrdersListPage(){
    orderListWidget = new OrderListWidget(this);
    this->centralWidget->setParent(0);
    this->setCentralWidget(orderListWidget);
}
