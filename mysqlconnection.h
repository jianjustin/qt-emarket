#ifndef MYSQLCONNECTION_H
#define MYSQLCONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QTextCodec>
#include <QDebug>
#include <QPluginLoader>

class MysqlConnection
{

public:
    MysqlConnection();
    void loadMySqlDriver();
    bool creatConnect();
    QSqlDatabase db;//MySQL数据库连接
    ~MysqlConnection();


};

#endif // MYSQLCONNECTION_H
