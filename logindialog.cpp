#include "logindialog.h"

#include <QFormLayout>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent)
{
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

    connect(loginButton,SIGNAL(clicked()),this,SLOT(on_loginButton_clicked()));

}


void LoginDialog::on_loginButton_clicked(){
    this->accept();
}

LoginDialog::~LoginDialog()
{

}

