#include "commoditylistwidget.h"

#include <QTableWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QStandardItem>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

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
    //清空
    tableModel->clear();
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

/**
 * 添加商品 - 面板弹出
 */
void CommodityListWidget::on_addButton_clicked(){
    commodityDetailDialog = new CommodityDetailDialog(1,-1);
    commodityDetailDialog->setWindowTitle("电子商城系统-添加商品");
    connect(commodityDetailDialog,SIGNAL(accepted()),this,SLOT(reloadTableData()));
    commodityDetailDialog->show();
}

/**
 * 删除商品
 */
void CommodityListWidget::on_delButton_clicked(){
    /*检查表格选中栏*/
    QModelIndexList selectedCommodities = commodityTable->selectionModel()->selectedRows();
    if(selectedCommodities.size() != 1){
        QMessageBox::warning(this,"","请选中一行数据进行删除");
        return;
    }

    /*确认是否删除*/
    QMessageBox::StandardButton defaultBtn = QMessageBox::NoButton;
    QMessageBox::StandardButton result;
    result = QMessageBox::question(this,"","是否确认删除",QMessageBox::Yes|QMessageBox::No,defaultBtn);
    if(result == QMessageBox::No)
        return;

    /*进行删除操作*/
    int itemID = tableModel->index(selectedCommodities[0].row(),0).data().toInt();
    QString sql = "delete from saleDB.commodity where CommodityID = :CommodityID";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":CommodityID",itemID);
    bool result1 = query.exec();

    if(result1)
        QMessageBox::information(this,"","删除商品成功");
    else
        QMessageBox::warning(this,"","删除商品异常，请联系管理员");
    initTableData();
}

/**
 * 修改商品 - 面板弹出
 */
void CommodityListWidget::on_editButton_clicked(){
    /*检查表格选中栏*/
    QModelIndexList selectedCommodities = commodityTable->selectionModel()->selectedRows();
    if(selectedCommodities.size() != 1){
        QMessageBox::warning(this,"","请选中一行数据进行修改");
        return;
    }

    /*初始化子面板*/
    int itemID = tableModel->index(selectedCommodities[0].row(),0).data().toInt();
    commodityDetailDialog = new CommodityDetailDialog(2,itemID);
    commodityDetailDialog->setWindowTitle("电子商城系统-修改商品");
    connect(commodityDetailDialog,SIGNAL(accepted()),this,SLOT(reloadTableData()));
    commodityDetailDialog->show();
}

/**
 * 查看商品 - 面板弹出
 */
void CommodityListWidget::on_showButton_clicked(){
    /*检查表格选中栏*/
    QModelIndexList selectedCommodities = commodityTable->selectionModel()->selectedRows();
    if(selectedCommodities.size() != 1){
        QMessageBox::warning(this,"","请选中一行数据进行查看");
        return;
    }

    /*初始化子面板*/
    int itemID = tableModel->index(selectedCommodities[0].row(),0).data().toInt();
    commodityDetailDialog = new CommodityDetailDialog(3,itemID);
    commodityDetailDialog->setWindowTitle("电子商城系统-商品详情");
    commodityDetailDialog->show();
}

/*重新加载表格数据*/
void CommodityListWidget::reloadTableData(){
    this->initTableData();
}
