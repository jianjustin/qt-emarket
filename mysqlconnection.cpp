#include "mysqlconnection.h"

MysqlConnection::MysqlConnection()
{
    loadMySqlDriver();
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    if(!creatConnect())qDebug() << "MySQL驱动加载成功";
}

MysqlConnection::~MysqlConnection(){}


void MysqlConnection::loadMySqlDriver() {
    QPluginLoader loader;
    loader.setFileName("/Users/jian/qt/5.11.1/clang_64/plugins/sqldrivers/libqsqlmysql.dylib");
    loader.load();
    if(!loader.isLoaded())
        qDebug() << loader.errorString();
    else
        qDebug() << "MySQL驱动加载成功";

}

bool MysqlConnection::creatConnect()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("saleDB");
    db.setUserName("root");
    db.setPassword("12345678");

    if(!db.open())
    {
        qDebug() << "连接数据库失败|||";
        qDebug() << db.lastError().text();
        return false;
    }
    else
    {
        qDebug() << "连接数据库成功";
        return true;
    }
}
