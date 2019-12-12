#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>


class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
private slots:
    void on_loginButton_clicked();
    void on_exitButton_clicked();
private:
    QPushButton *loginButton;
    QPushButton *exitButton;
    QLineEdit *username;
    QLineEdit *password;
};

#endif // LOGINDIALOG_H
