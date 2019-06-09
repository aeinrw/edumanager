#include "teacherwindow.h"
#include "ui_teacherwindow.h"

TeacherWindow::TeacherWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TeacherWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("老师面板");
    this->setFixedSize(400,300);
    this->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存

    openTable();
}

TeacherWindow::~TeacherWindow()
{
    delete ui;
}


void TeacherWindow::openTable()
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
        query.prepare("SELECT id,name,password FROM teacher WHERE id=:ID");
        query.bindValue(":ID",LoginId);
        query.exec();
        query.first();

        ui->editId->setText(query.value("id").toString());
        ui->editName->setText(query.value("name").toString());
        ui->editPassword->setText(query.value("password").toString());

}



void TeacherWindow::on_pushButton_clicked()
{
    QSqlQuery modify;
    modify.prepare("UPDATE teacher SET password=? WHERE id=?");
    modify.bindValue(0,ui->editPassword->text());
    modify.bindValue(1,LoginId);
    if(modify.exec())
        QMessageBox::information(this, "提示", "密码修改成功");
    else
        QMessageBox::warning(this,"错误","修改密码失败,错误信息\n"
                             +modify.lastError().text(),QMessageBox::Ok,QMessageBox::NoButton);
}
