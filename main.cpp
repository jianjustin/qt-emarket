#include "mainwindow.h"
#include "logindialog.h"
#include "mysqlconnection.h"
#include <QApplication>

/**
 * 网上MINI电子商城系统
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MysqlConnection *mysqlConnection = new MysqlConnection;

    LoginDialog *loginDialog = new LoginDialog();
    if(loginDialog->exec() == QDialog::Accepted){
        MainWindow w;
        w.show();
        return a.exec();
    }else
        return 0;


}
