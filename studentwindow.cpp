#include "studentwindow.h"
#include "ui_studentwindow.h"
#include <QDebug>

StudentWindow::StudentWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("学生面板");
    this->setFixedSize(400,300);
    this->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存

    openTable();


}

StudentWindow::~StudentWindow()
{
    delete ui;
}

void StudentWindow::openTable()
{
    db=QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName(DB_HOSTNAME);
    db.setDatabaseName(DB_NAME);
    db.setUserName(DB_USERNAME);
    db.setPassword(DB_PASSWORD);

    if(!db.open())
    {
        QMessageBox::warning(this,"错误","打开数据库失败,错误信息\n"
                             +db.lastError().text(),QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT id,name,class,password FROM student WHERE id=:ID");
    query.bindValue(":ID",LoginId);
    query.exec();
    query.first();

    ui->editId->setText(query.value("id").toString());
    ui->editClass->setText(query.value("class").toString());
    ui->editName->setText(query.value("name").toString());
    ui->editPassword->setText(query.value("password").toString());

}


void StudentWindow::on_btnChange_clicked()
{
    QSqlQuery modify;
    modify.prepare("UPDATE student SET password=? WHERE id=?");
    modify.bindValue(0,ui->editPassword->text());
    modify.bindValue(1,LoginId);
    if(modify.exec())
        QMessageBox::information(this, "提示", "密码修改成功");
    else
        QMessageBox::warning(this,"错误","修改密码失败,错误信息\n"
                             +modify.lastError().text(),QMessageBox::Ok,QMessageBox::NoButton);

}
