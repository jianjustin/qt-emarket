#include "orderlistwidget.h"

/**
 * 订单模块
 */
OrderListWidget::OrderListWidget(QMainWindow *mainWindow,QWidget *parent) : QWidget(parent)
{
    //显示订单列表
    mainWindow->setWindowTitle("e电子商城系统 - 订单");

    //按钮组
    showButton = new QPushButton("订单详情");
    addButton = new QPushButton("添加订单");
    connect(addButton,SIGNAL(clicked()),this,SLOT(on_addButton_clicked()));
    connect(showButton,SIGNAL(clicked()),this,SLOT(on_showButton_clicked()));

    //订单列表
    initOrderTable();//初始化表格

    //布局
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(addButton,0,0,1,1);
    mainLayout->addWidget(showButton,0,1,1,1);
    mainLayout->addWidget(orderTable,1,0,6,6);

}

/**
 * 初始化订单表格（用于初始化表格样式）
 */
void OrderListWidget::initOrderTable(){
    orderTable = new QTableView;
    initTableModel();//初始化表头
    orderTable->setModel(tableModel);
    initTableData();
}

/**
 * 初始化订单表格表头
 */
void OrderListWidget::initTableModel(){
    tableModel = new QStandardItemModel;
    tableModel->setColumnCount(6);
    tableModel->setHeaderData(0,Qt::Horizontal,"ID");
    tableModel->setHeaderData(1,Qt::Horizontal,"分类");
    tableModel->setHeaderData(2,Qt::Horizontal,"名称");
    tableModel->setHeaderData(3,Qt::Horizontal,"购入价格");
    tableModel->setHeaderData(4,Qt::Horizontal,"售出价格");
    tableModel->setHeaderData(5,Qt::Horizontal,"库存");
}

/**
 * 初始化表格数据
 */
void OrderListWidget::initTableData(){

}

/**
 * 添加订单
 */
void OrderListWidget::on_addButton_clicked(){
    orderDetailsDialog = new OrderDetailsDialog(1,-1);
    orderDetailsDialog->setWindowTitle("电子商城系统-添加订单");
    connect(orderDetailsDialog,SIGNAL(accepted()),this,SLOT(reloadTableData()));
    orderDetailsDialog->show();
}

/**
 * 显示订单
 */
void OrderListWidget::on_showButton_clicked(){
    orderDetailsDialog = new OrderDetailsDialog(1,-1);
    orderDetailsDialog->setWindowTitle("电子商城系统-添加订单");
    connect(orderDetailsDialog,SIGNAL(accepted()),this,SLOT(reloadTableData()));
    orderDetailsDialog->show();
}

/**
 * 重新加载表格数据
 */
void OrderListWidget::reloadTableData(){

}

OrderListWidget::~OrderListWidget(){}
