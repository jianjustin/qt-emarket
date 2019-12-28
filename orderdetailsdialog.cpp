#include "orderdetailsdialog.h"

#include <QSpinBox>
#include <QVariantList>

OrderDetailsDialog::OrderDetailsDialog(int flag,QString orderDetailsID, QDialog *parent) : QDialog(parent)
{
    //堵塞父窗口并显示子窗口
    Qt::WindowFlags flags = Qt::Dialog;
    this->setWindowFlags(flags);
    this->setWindowModality(Qt::ApplicationModal);

    this->flag = flag;
    this->orderDetailsID = orderDetailsID;

    mainLayout = new QHBoxLayout(this);//添加主布局
    initCommodityData();//加载商品基础数据
    OrderItem *item = new OrderItem();
    orderItemList.append(*item);

    if(1 == flag)
        showOrderDetailsPage();
    else
        addOrderDetailsPage();
}

void OrderDetailsDialog::addOrderDetailsPage(){
    QFormLayout *leftLayout = new QFormLayout;

    orderID = new QLineEdit;
    memberID = new QLineEdit;
    paySum = new QLineEdit;
    payWay = new QLineEdit;
    orderTime = new QDateTimeEdit;
    QPushButton *orderPaySumButton = new QPushButton("计算金额");
    QPushButton *orderPayButton = new QPushButton("下单");

    orderID->setText(createOrderIDByUUID());//初始化订单编号
    orderID->setEnabled(false);
    orderPayButton->setFixedWidth(80);

    QDateTime time = QDateTime::currentDateTime();//设置时间
    orderTime->setDateTime(time);
    paySum->setText("0");//设置支付金额

    leftLayout->addRow("订单编号：",orderID);
    leftLayout->addRow("用户：",memberID);
    leftLayout->addRow("支付金额",paySum);
    leftLayout->addRow("支付方式",payWay);
    //leftLayout->addRow("订单时间",orderTime);
    leftLayout->addRow(orderPaySumButton,orderPayButton);

    QGridLayout *rightLayout = new QGridLayout;//右侧订单商品模块
    addCommodityButton = new QPushButton("添加商品");
    delCommodityButton = new QPushButton("删除商品");
    connect(addCommodityButton,SIGNAL(clicked()),this,SLOT(on_addCommodityButton_clicked()));
    connect(delCommodityButton,SIGNAL(clicked()),this,SLOT(on_delCommodityButton_clicked()));
    loadOrderItemTable();//初始化订单商品表格

    connect(orderPaySumButton,SIGNAL(clicked()),this,SLOT(on_orderPaySumButton_clicked()));
    connect(orderPayButton,SIGNAL(clicked()),this,SLOT(on_orderPayButton_clicked()));

    //rightLayout->addWidget(addCommodityButton,0,0,1,1);
    rightLayout->addWidget(delCommodityButton,0,0,1,1);
    rightLayout->addWidget(orderItemTable,1,0,6,6);
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

}

void OrderDetailsDialog::showOrderDetailsPage(){

}

/**
 * 基于QList加载订单商品表格
 */
void OrderDetailsDialog::loadOrderItemTable(){
    orderItemTable = new QTableView;
    orderItemTable->setFixedSize(400,300);
    orderItemTableModel = new QStandardItemModel;
    orderItemTableModel->setColumnCount(2);
    orderItemTableModel->setHeaderData(0,Qt::Horizontal,"商品名称");
    orderItemTableModel->setHeaderData(1,Qt::Horizontal,"购买数量");
    orderItemTable->setModel(orderItemTableModel);
    loadOrderItemTableData();
}

/**
 * 基于orderItemList加载表格数据
 */
void OrderDetailsDialog::loadOrderItemTableData(){
    orderItemTableModel->removeRows(0,orderItemTableModel->rowCount());
    for(int i=0; i<orderItemList.size(); i++){
        QSpinBox *upperSpinBoxItem = new QSpinBox();//数量动态选择框
        upperSpinBoxItem->setValue(orderItemList[i].count);
        QComboBox *commodityQComboBox = createQComboBox(orderItemList[i].name);
        orderItemTableModel->setItem(i,0,new QStandardItem(orderItemList[i].name));
        orderItemTable->setIndexWidget(orderItemTableModel->index(i,0),commodityQComboBox);
        orderItemTable->setIndexWidget(orderItemTableModel->index(i,1),upperSpinBoxItem);
    }
}

/**
 * 订单商品添加
 */
void OrderDetailsDialog::on_addCommodityButton_clicked(){
    OrderItem *item = new OrderItem();
    orderItemList.append(*item);
    loadOrderItemTableData();
}

/**
 * 订单商品删除
 */
void OrderDetailsDialog::on_delCommodityButton_clicked(){
    QModelIndexList selectedCommodities = orderItemTable->selectionModel()->selectedRows();
    if(selectedCommodities.size() != 1){
        QMessageBox::warning(this,"","请选中一行数据进行删除");
        return;
    }
    orderItemList.removeAt(selectedCommodities[0].row());
    loadOrderItemTableData();
}

void OrderDetailsDialog::initCommodityData(){
    //商品列表显示
    QString sql = "select CommodityID,CategoryID,Name,InputPrice,OutputPrice,Amount from saleDB.commodity";
    QSqlQuery query;
    query.exec(sql);

    while(query.next()){
        Commodity *commodity = new Commodity();
        commodity->commodityID = query.value(0).toInt();
        commodity->CategoryID = query.value(1).toInt();
        commodity->name = query.value(2).toString();
        commodity->InputPrice = query.value(3).toFloat();
        commodity->OutputPrice = query.value(4).toFloat();
        commodity->Amount = query.value(5).toInt();
        commodityList.append(*commodity);
        OrderItem *orderItem = new OrderItem();//初始化订单商品
        orderItem->commodityID = commodity->commodityID;
        orderItem->CategoryID = commodity->CategoryID;
        orderItem->name = commodity->name;
        orderItem->InputPrice = commodity->InputPrice;
        orderItem->OutputPrice = commodity->OutputPrice;
        orderItem->Amount = commodity->Amount;
        orderItem->count = 1;
        orderItemMap[query.value(2).toString()] = *orderItem;
    }
}

/**
 * 创建商品下拉项
 */
QComboBox* OrderDetailsDialog::createQComboBox(QString showName){
    QComboBox *commodityQComboBox = new QComboBox;
    commodityQComboBox->addItem(showName);
    for(int i=0 ; i < commodityList.length() ; i++){
            commodityQComboBox->addItem(commodityList[i].name);
    }
    connect(commodityQComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_com_text_currentTextChanged(QString)));//初始化订单商品数据
    return commodityQComboBox;
}


void OrderDetailsDialog::on_com_text_currentTextChanged(const QString &arg1)
{
    qDebug() <<"Text:"<<arg1;
    OrderItem *item = &(orderItemMap[arg1]);
    orderItemList.removeLast();
    orderItemList.append(*item);
    OrderItem *item1 = new OrderItem();
    orderItemList.append(*item1);
    loadOrderItemTableData();
}

void OrderDetailsDialog::on_orderPaySumButton_clicked(){
    float sum = 0;
    for(int i = 0 ; i < orderItemList.length()-1 ; i++){
        sum += orderItemList[i].OutputPrice*orderItemList[i].count;
    }
    paySum->setText(QString::number(sum));
}

void OrderDetailsDialog::on_orderPayButton_clicked(){
    /*数据校验*/
    QString orderIDStr = orderID->text();
    int memberIDValue = memberID->text().toInt();
    float paySumValue = paySum->text().toFloat();
    float payWayValue = payWay->text().toFloat();

    /*插入操作*/
    QString sql = "insert into saleDB.orders(OrderID,MemberID,PaySum,PayWay) value(:OrderID,:MemberID,:PaySum,:PayWay)";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":OrderID",orderIDStr);
    query.bindValue(":MemberID",memberIDValue);
    query.bindValue(":PaySum",paySumValue);
    query.bindValue(":PayWay",payWayValue);
    bool result = query.exec();

    /*执行子订单生成*/
    QVariantList OrderIDList;
    QVariantList commodityList;
    sql = "insert into saleDB.orderitems(OrderID,CommodityID,Count) values(:OrderID,:CommodityID,:Count)";
    for(int i = 0 ; i < orderItemList.length()-1 ; i++){
        query.prepare(sql);
        query.bindValue(":OrderID",orderIDStr);
        query.bindValue(":CommodityID",orderItemList[i].commodityID);
        query.bindValue(":Count",orderItemList[i].count);
        result = result&&query.exec();
    }

    if(result){
        QMessageBox::information(this,"","添加订单信息成功");
    }else{
        QMessageBox::warning(this,"","添加订单异常，请联系管理员");
    }
}

/**
 * 创建订单编号-UUID
 */
QString OrderDetailsDialog::createOrderIDByUUID(){
    QUuid id = QUuid::createUuid();
    QString strId = id.toString();
    qDebug() << strId;

    strId.remove("{").remove("}");
    return strId;
}

OrderDetailsDialog::~OrderDetailsDialog(){}
