#ifndef ORDERDETAILSDIALOG_H
#define ORDERDETAILSDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QUuid>
#include <QFormLayout>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMessageBox>
#include <QSqlQuery>
#include <QComboBox>
#include <QDebug>
#include <QDateTimeEdit>
#include <QDateTime>
#include <QMap>

/*订单商品信息*/
typedef struct OrderItem
{
    int commodityID;
    QString name;
    int count;
    int CategoryID;
    float InputPrice;
    float OutputPrice;
    int Amount;
    void (*func)();
}OrderItem;

/*商品基本信息*/
typedef struct Commodity
{
    int commodityID;
    int CategoryID;
    QString name;
    float InputPrice;
    float OutputPrice;
    int Amount;
    void (*func)();
}Commodity;

class OrderDetailsDialog : public QDialog
{
    Q_OBJECT
public:
    OrderDetailsDialog(int flag,QString orderDetailsID,QDialog *parent=0);
    QString createOrderIDByUUID();
    void showOrderDetailsPage();
    void addOrderDetailsPage();
    void loadOrderItemTable();
    void loadOrderItemTableData();
    void initCommodityData();
    QComboBox* createQComboBox(QString showName);

    ~OrderDetailsDialog();

private slots:
    void on_addCommodityButton_clicked();
    void on_delCommodityButton_clicked();
    void on_orderPaySumButton_clicked();
    void on_orderPayButton_clicked();
    void on_com_text_currentTextChanged(const QString &arg1);

private:
    int flag;
    QString orderDetailsID;
    QHBoxLayout *mainLayout;

    QLineEdit *orderID;//订单主信息
    QLineEdit *memberID;
    QLineEdit *paySum;
    QLineEdit *payWay;
    QDateTimeEdit *orderTime;

    QList<OrderItem> orderItemList;//订单商品列表
    QMap<QString,OrderItem> orderItemMap;
    QTableView *orderItemTable;
    QStandardItemModel *orderItemTableModel;
    QPushButton *addCommodityButton;
    QPushButton *delCommodityButton;

    QList<Commodity> commodityList;//商品信息，用于加载下拉项
};

#endif // ORDERDETAILSDIALOG_H
