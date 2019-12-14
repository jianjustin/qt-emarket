#ifndef COMMODITYDETAILDIALOG_H
#define COMMODITYDETAILDIALOG_H

#include <QDialog>
#include <QMainWindow>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>

class CommodityDetailDialog : public QDialog
{
    Q_OBJECT
public:
    CommodityDetailDialog(int flag,int commodityDetailDialogID,QDialog *parent=0);
    void initDetailDialog();
    void initCommodityData();
    void setQLineEditUnable();
    ~CommodityDetailDialog();
private slots:
    void on_exitButton_clicked();
    void on_editButton_clicked();
    void on_saveButton_clicked();
private:
    QLineEdit *categoryID;
    QLineEdit *name;
    QLineEdit *picture;
    QLineEdit *inputPrice;
    QLineEdit *outputPrice;
    QLineEdit *amount;
    int flag;
    int commodityDetailDialogID;
};

#endif // COMMODITYDETAILDIALOG_H
