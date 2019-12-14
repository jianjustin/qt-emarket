#ifndef COMMODITYDETAILDIALOG_H
#define COMMODITYDETAILDIALOG_H

#include <QDialog>
#include <QMainWindow>

class CommodityDetailDialog : public QDialog
{
    Q_OBJECT
public:
    CommodityDetailDialog(int commodityDetailDialogID,QDialog *parent=0);
    ~CommodityDetailDialog();
};

#endif // COMMODITYDETAILDIALOG_H
