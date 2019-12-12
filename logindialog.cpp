#include "logindialog.h"

#include <QFormLayout>

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
    this->accept();
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

