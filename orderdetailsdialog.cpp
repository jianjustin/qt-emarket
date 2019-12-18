#include "orderdetailsdialog.h"

OrderDetailsDialog::OrderDetailsDialog(int flag,int orderDetailsID, QDialog *parent) : QDialog(parent)
{
    //堵塞父窗口并显示子窗口
    Qt::WindowFlags flags = Qt::Dialog;
    this->setWindowFlags(flags);
    this->setWindowModality(Qt::ApplicationModal);

    this->flag = flag;
    this->orderDetailsID = orderDetailsID;
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
