#include "login.h"
#include "ui_login.h"


Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    //设置固定大小
    this->setFixedSize(500,400);
    //设置标题
    this->setWindowTitle("教务管理系统");

//    ui->editPassword->setText("admin");
//    ui->editUsername->setText("admin");

    ui->rbtnAdmin->setChecked(true);

    if(!database_connection())
    {
        QMessageBox::warning(this,"错误","打开数据库失败",QMessageBox::Ok,QMessageBox::NoButton);
    }

}

Login::~Login()
{
    delete ui;
}

bool Login::database_connection()
{
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(DB_HOSTNAME);
    db.setDatabaseName(DB_NAME);
    db.setUserName(DB_USERNAME);
    db.setPassword(DB_PASSWORD);


    if(db.open())
        return true;
    else
        return false;

}

//退出按钮
void Login::on_btnQuit_clicked()
{
    this->close();
}

//重置按钮
void Login::on_btnReset_clicked()
{
    ui->editPassword->clear();
    ui->editUsername->clear();
}

//登陆按钮
void Login::on_btnLogin_clicked()
{
    QString Id=ui->editUsername->text();
    QString Password=ui->editPassword->text();

    //管理员登陆
    if(ui->rbtnAdmin->isChecked())
    {
        if(match_name_password(Id,Password,"admin"))
        {
            qDebug()<<"管理员登陆成功";
            QMessageBox::information(this, "提示", "管理员登陆成功");
            this->hide();
            AdminWindow *admin=new AdminWindow;
            admin->show();

        }
        else
            QMessageBox::information(this, "警告", "用户名或密码错误");
    }

    //教师登陆
    if(ui->rbtnTeacher->isChecked())
    {
        if(match_name_password(Id,Password,"teacher"))
        {
            LoginId=Id;
            qDebug()<<"教师登陆成功";
            QMessageBox::information(this, "提示", "老师登陆成功");

            this->hide();
            TeacherWindow *teacher=new TeacherWindow;
            teacher->show();

        }
        else
            QMessageBox::information(this, "警告", "用户名或密码错误");
    }

    //学生登陆
    if(ui->rbtnStudent->isChecked())
    {
        if(match_name_password(Id,Password,"student"))
        {
            LoginId=Id;
            qDebug()<<"学生登陆成功";
            QMessageBox::information(this, "提示", "学生登陆成功");
            this->hide();
            StudentWindow *student=new StudentWindow;
            student->show();

        }
        else
            QMessageBox::information(this, "警告", "用户名或密码错误");
    }

}

bool Login::match_name_password(QString ID,QString PASSWORD,QString table)
{
    QString select="select id,password from ";
    QSqlQuery query(db);

    query.exec(select+table);
    bool flag=false;
    while(query.next())
    {
        QString id = query.value(0).toString();
        QString password = query.value(1).toString();
        //qDebug() << id << password ;
        if(ID.compare(id)==0 && PASSWORD.compare(password)==0)
            flag=true;
    }
    return flag;
}



