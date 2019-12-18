#ifndef ORDERDETAILSDIALOG_H
#define ORDERDETAILSDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QUuid>

class OrderDetailsDialog : public QDialog
{
public:
    OrderDetailsDialog(int flag,int orderDetailsID,QDialog *parent=0);
    QString createOrderIDByUUID();
    ~OrderDetailsDialog();

private:
    int flag;
    int orderDetailsID;

};

#endif // ORDERDETAILSDIALOG_H
