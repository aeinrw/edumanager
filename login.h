#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

#include "globle.h"
#include "adminwindow.h"
#include "studentwindow.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    //连接数据库
    bool database_connection();

    //匹配登陆信息
    bool match_name_password(QString ID,QString PASSWORD,QString table);

private slots:
    void on_btnQuit_clicked();

    void on_btnReset_clicked();

    void on_btnLogin_clicked();

private:
    Ui::Login *ui;
    QSqlDatabase db;
};

#endif // LOGIN_H
