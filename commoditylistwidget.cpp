#include "commoditylistwidget.h"

#include <QTableWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QStandardItem>


CommodityListWidget::CommodityListWidget(QMainWindow *mainWindow,QWidget *parent) : QWidget(parent)
{
    mainWindow->setWindowTitle("e电子商城系统 - 商品列表");

    QPushButton *button1 = new QPushButton("增加");
    QPushButton *button2 = new QPushButton("删除");
    QPushButton *button3 = new QPushButton("修改");
    QPushButton *button4 = new QPushButton("查看");

    initCommodityTable();//初始化表格

    //布局
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(button1,0,0,1,1);
    mainLayout->addWidget(button2,0,1,1,1);
    mainLayout->addWidget(button3,0,2,1,1);
    mainLayout->addWidget(button4,0,3,1,1);
    mainLayout->addWidget(commodityTable,1,0,6,6);
}

CommodityListWidget::~CommodityListWidget()
{

}

/**
 * 初始化商品表格（用于初始化表格样式）
 */
void CommodityListWidget::initCommodityTable(){
    commodityTable = new QTableView;
    initTableModel();//初始化表头
    commodityTable->setModel(tableModel);
    initTableData();
}

/**
 * 初始化商品表格表头
 */
void CommodityListWidget::initTableModel(){
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
void CommodityListWidget::initTableData(){
    QStandardItem *item;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<6;j++)
        {
                    item = new QStandardItem(QString::number(j));
                    tableModel->setItem(i,j,item);
        }
    }

}
