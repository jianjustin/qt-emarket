#ifndef ORDERLISTWIDGET_H
#define ORDERLISTWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QStandardItemModel>
#include <QTableView>
#include <QMainWindow>

#include "orderdetailsdialog.h"

class OrderListWidget : public QWidget
{
    Q_OBJECT
public:
    OrderListWidget(QMainWindow *mainWindow,QWidget *parent = 0);
    void initOrderTable();
    void initTableModel();
    void initTableData();
    ~OrderListWidget();
signals:

public slots:
    void on_addButton_clicked();
    void on_showButton_clicked();
    void reloadTableData();

private:
    OrderDetailsDialog *orderDetailsDialog;

    QPushButton *showButton;//显示订单详情
    QPushButton *addButton;//添加订单

    QStandardItemModel *tableModel;//订单数据model
    QTableView *orderTable;//订单列表
};

#endif // ORDERLISTWIDGET_H
