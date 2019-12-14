#ifndef COMMODITYLISTWIDGET_H
#define COMMODITYLISTWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableView>
#include <QPushButton>

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
   void on_addButton_clicked();
   void on_delButton_clicked();
   void on_editButton_clicked();
   void on_showButton_clicked();
private:
    QStandardItemModel *tableModel;
    QTableView *commodityTable;
    //按钮组
    QPushButton *addButton;
    QPushButton *delButton;
    QPushButton *editButton;
    QPushButton *showButton;

};

#endif // COMMODITYLISTWIDGET_H
