#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("e电子商城系统");
    this->setStyleSheet("QMainWindow {background: '#e9e9e9';}");//设置背景颜色
    this->setFixedSize(800,600);
    createActions();
    createMenus();

    //默认主页，参考"defaultcentralwidget.h"
    centralWidget = new DefaultCentralWidget(this);
    this->setCentralWidget(centralWidget);

}


MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
    showGoodsAction = new QAction("查看",this);
    connect(showGoodsAction,SIGNAL(triggered()),this,SLOT (showCommodityListPage()));
    addGoodsAction =new QAction("添加",this);
    connect(addGoodsAction,SIGNAL(triggered()),this,SLOT (addCommodity()));
    logoutAction = new QAction("登出",this);
}

void MainWindow::createMenus(){
    goodsMenu = menuBar()->addMenu("商品");
    goodsMenu->addAction(showGoodsAction);
    goodsMenu->addAction(addGoodsAction);
    systemMenu = menuBar()->addMenu("系统");
    systemMenu->addAction(logoutAction);
}

/**
 * 显示商品列表
 */
void MainWindow::showCommodityListPage(){
    commodityListWidget = new CommodityListWidget(this);
    this->centralWidget->setParent(0);
    this->setCentralWidget(commodityListWidget);
}

/**
 * 添加商品详情
 */
void MainWindow::addCommodity(){
    addCommodityWidget = new AddCommodityWidget(this);
    this->centralWidget->setParent(0);
    this->setCentralWidget(addCommodityWidget);
}
