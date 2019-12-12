#ifndef COMMODITYLISTWIDGET_H
#define COMMODITYLISTWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableView>

class CommodityListWidget : public QWidget
{
    Q_OBJECT
public:
    CommodityListWidget(QMainWindow *mainWindow,QWidget *parent = 0);
    void initCommodityTable();
    void initTableModel();
    void initTableData();
    ~CommodityListWidget();
private slots:

private:
    QStandardItemModel *tableModel;
    QTableView *commodityTable;

};

#endif // COMMODITYLISTWIDGET_H
