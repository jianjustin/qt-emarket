#include "logindialog.h"

#include <QFormLayout>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("e电子商城系统 - 登录");
    QFormLayout *layout = new QFormLayout(this);

    username = new QLineEdit;
    password = new QLineEdit;
    password->setEchoMode(QLineEdit::Password);//设置输入框类型
    loginButton = new QPushButton("登录");
    exitButton = new QPushButton("退出");
    layout->addRow("用户名：",username);
    layout->addRow("密  码：",password);
    layout->addRow(loginButton);
    layout->addRow(exitButton);

    connect(loginButton,SIGNAL(clicked()),this,SLOT(on_loginButton_clicked()));//连接登录操作
    connect(exitButton,SIGNAL(clicked()),this,SLOT(on_exitButton_clicked()));//连接退出系统操作
}

/**
 * 登录操作
 * @todo 连接数据库进行数据库操作
 */
void LoginDialog::on_loginButton_clicked(){
    qDebug() << "======================开始登录======================";
    QString sql = "select * from saleDB.member where Name = :name and PassWord = :password";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":name",username->text());
    query.bindValue(":password",password->text());
    query.exec();
    if(query.next()){
        this->accept();
        qDebug() << "======================登录成功======================";
    }else
        QMessageBox::warning(this,"登录失败","用户名或密码错误，请重新输入");
}

/**
 * 退出系统
 */
void LoginDialog::on_exitButton_clicked(){
    this->reject();
}

LoginDialog::~LoginDialog()
{

}

