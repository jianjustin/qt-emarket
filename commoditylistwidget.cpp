#include "commoditylistwidget.h"

#include "commoditydetaildialog.h"

#include <QTableWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QStandardItem>
#include <QSqlQuery>
#include <QDebug>


CommodityListWidget::CommodityListWidget(QMainWindow *mainWindow,QWidget *parent) : QWidget(parent)
{
    mainWindow->setWindowTitle("e电子商城系统 - 商品列表");

    //初始化按钮
    addButton = new QPushButton("添加商品");
    delButton = new QPushButton("删除商品");
    editButton = new QPushButton("修改商品");
    showButton = new QPushButton("查看商品详情");

    connect(addButton,SIGNAL(clicked()),this,SLOT(on_addButton_clicked()));
    connect(delButton,SIGNAL(clicked()),this,SLOT(on_delButton_clicked()));
    connect(editButton,SIGNAL(clicked()),this,SLOT(on_editButton_clicked()));
    connect(showButton,SIGNAL(clicked()),this,SLOT(on_showButton_clicked()));

    initCommodityTable();//初始化表格

    //布局
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(addButton,0,0,1,1);
    mainLayout->addWidget(delButton,0,1,1,1);
    mainLayout->addWidget(editButton,0,2,1,1);
    mainLayout->addWidget(showButton,0,3,1,1);
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
    //商品列表显示
    QString sql = "select CommodityID,CategoryID,Name,InputPrice,OutputPrice,Amount from saleDB.commodity";
    QSqlQuery query;
    query.exec(sql);

    QStandardItem *item;
    int i = 0;
    while(query.next()){
        for(int j=0;j<6;j++){
            item = new QStandardItem(query.value(j).toString());
            tableModel->setItem(i,j,item);
        }
        i++;
    }
}

void CommodityListWidget::on_addButton_clicked(){
    CommodityDetailDialog *commodityDetailDialog = new CommodityDetailDialog(-1);
}

void CommodityListWidget::on_delButton_clicked(){
    QModelIndexList selectedCommodities = commodityTable->selectionModel()->selectedRows();
    for (int i = 0; i < selectedCommodities.size(); i++)
    {
        qDebug() << selectedCommodities[i].data(Qt::DisplayRole).toString();

        qDebug() << tableModel->index(selectedCommodities[i].row(),0).data().toString();
        qDebug() << tableModel->index(selectedCommodities[i].row(),1).data().toString();
        qDebug() << tableModel->index(selectedCommodities[i].row(),2).data().toString();
        qDebug() << tableModel->index(selectedCommodities[i].row(),3).data().toString();
        qDebug() << tableModel->index(selectedCommodities[i].row(),4).data().toString();
        qDebug() << tableModel->index(selectedCommodities[i].row(),5).data().toString();
        qDebug() << "==========================";
    }
}

void CommodityListWidget::on_editButton_clicked(){

}

void CommodityListWidget::on_showButton_clicked(){

}
