#include "commoditydetaildialog.h"

#include <QMessageBox>
#include <QSqlQuery>

/**
 * 商品详情弹出页
 * 1. 添加商品详情 - 不包含内容，可添加
 * 2. 商品详情修改 - 包含内容，可修改
 * 3. 显示商品详情 - 包含内容，不可修改
 */
CommodityDetailDialog::CommodityDetailDialog(int flag,int commodityDetailDialogID, QDialog *parent) : QDialog(parent)
{
    //堵塞父窗口并显示子窗口
    Qt::WindowFlags flags = Qt::Dialog;
    this->setWindowFlags(flags);
    this->setWindowModality(Qt::ApplicationModal);

    this->flag = flag;
    this->commodityDetailDialogID = commodityDetailDialogID;
    //根据操作说明初始化面板
    initDetailDialog();
}

CommodityDetailDialog::~CommodityDetailDialog(){

}

/**
 * 新增商品页面初始化
 */
void CommodityDetailDialog::initDetailDialog(){
    QFormLayout *layout = new QFormLayout(this);

    categoryID = new QLineEdit;
    name = new QLineEdit;
    picture = new QLineEdit;
    inputPrice = new QLineEdit;
    outputPrice = new QLineEdit;
    amount = new QLineEdit;

    if(2 == flag || flag == 3)initCommodityData();//初始化商品详情数据
    if(3 == flag)setQLineEditUnable();//设置不可编辑

    QPushButton *editButton = new QPushButton("保存");
    QPushButton *saveButton = new QPushButton("添加");
    QPushButton *exitButton = new QPushButton("退出");
    connect(editButton,SIGNAL(clicked()),this,SLOT(on_editButton_clicked()));
    connect(saveButton,SIGNAL(clicked()),this,SLOT(on_saveButton_clicked()));
    connect(exitButton,SIGNAL(clicked()),this,SLOT(on_exitButton_clicked()));
    layout->addRow("商品名称：",name);
    layout->addRow("商品分类：",categoryID);
    layout->addRow("商品图片：",picture);
    layout->addRow("购入价：",inputPrice);
    layout->addRow("售出价：",outputPrice);
    layout->addRow("商品库存：",amount);
    if(2 == flag)layout->addRow(editButton);
    if(1 == flag)layout->addRow(saveButton);
    layout->addRow(exitButton);
}

void CommodityDetailDialog::on_saveButton_clicked(){
    /*数据校验*/
    QString nameStr = name->text();
    QString categoryStr = categoryID->text();
    QString pictureStr = picture->text();
    float inputPriceValue = inputPrice->text().toFloat();
    float outputPriceValue = outputPrice->text().toFloat();
    int amountValue = amount->text().toInt();

    /*插入操作*/
    QString sql = "insert into saleDB.commodity(Name,CategoryID,Picture,InputPrice,OutputPrice,Amount) value(:Name,:CategoryID,:Picture,:InputPrice,:OutputPrice,:Amount)";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":Name",nameStr);
    query.bindValue(":CategoryID",categoryStr);
    query.bindValue(":Picture",pictureStr);
    query.bindValue(":InputPrice",inputPriceValue);
    query.bindValue(":OutputPrice",outputPriceValue);
    query.bindValue(":Amount",amountValue);
    bool result = query.exec();

    if(result){
        QMessageBox::information(this,"","添加商品信息成功");
    }else{
        QMessageBox::warning(this,"","添加商品异常，请联系管理员");
    }
}

void CommodityDetailDialog::on_editButton_clicked(){
    /*数据校验*/
    QString nameStr = name->text();
    QString categoryStr = categoryID->text();
    QString pictureStr = picture->text();
    float inputPriceValue = inputPrice->text().toFloat();
    float outputPriceValue = outputPrice->text().toFloat();
    int amountValue = amount->text().toInt();

    /*修改操作*/
    QString sql = "update saleDB.commodity set Name=:Name,CategoryID=:CategoryID,Picture=:Picture,InputPrice=:InputPrice,OutputPrice=:OutputPrice,Amount=:Amount";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":Name",nameStr);
    query.bindValue(":CategoryID",categoryStr);
    query.bindValue(":Picture",pictureStr);
    query.bindValue(":InputPrice",inputPriceValue);
    query.bindValue(":OutputPrice",outputPriceValue);
    query.bindValue(":Amount",amountValue);
    bool result = query.exec();

    if(result){
        QMessageBox::information(this,"","修改商品信息成功");
    }else{
        QMessageBox::warning(this,"","修改商品异常，请联系管理员");
    }
}

void CommodityDetailDialog::initCommodityData(){
    QString sql = "select Name,CategoryID,Picture,InputPrice,OutputPrice,Amount from saleDB.commodity where CommodityID = :CommodityID";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":CommodityID",this->commodityDetailDialogID);
    query.exec();
    if(query.next()){
        name->setText(query.value(0).toString());
        categoryID->setText(query.value(1).toString());
        picture->setText(query.value(2).toString());
        inputPrice->setText(query.value(3).toString());
        outputPrice->setText(query.value(4).toString());
        amount->setText(query.value(5).toString());
    }else{
        QMessageBox::warning(this,"","查询商品详情异常，请联系管理员");
        this->accept();
    }
}

/**
 * 设置不可编辑
 */
void CommodityDetailDialog::setQLineEditUnable(){
    categoryID->setReadOnly(true);
    name->setReadOnly(true);
    picture->setReadOnly(true);
    inputPrice->setReadOnly(true);
    outputPrice->setReadOnly(true);
    amount->setReadOnly(true);
}
/**
 * 退出商品详情面板
 */
void CommodityDetailDialog::on_exitButton_clicked(){
    this->accept();
}


