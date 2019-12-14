#include "commoditydetaildialog.h"

/**
 * 商品详情弹出页
 * 1. 显示商品详情 - 包含内容，不可修改
 * 2. 商品详情修改 - 包含内容，可修改
 * 3. 添加商品详情 - 不包含内容，可添加
 */
CommodityDetailDialog::CommodityDetailDialog(int commodityDetailDialogID, QDialog *parent) : QDialog(parent)
{
    //堵塞父窗口并显示子窗口
    Qt::WindowFlags flags = Qt::Dialog;
    this->setWindowFlags(flags);
    this->setWindowModality(Qt::ApplicationModal);
    this->show();

    if(-1 == commodityDetailDialogID)
        this->setWindowTitle("e电子商城系统-新增商品");
}

CommodityDetailDialog::~CommodityDetailDialog(){
    this->exec();
}


