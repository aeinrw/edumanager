#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("管理员面板");
    this->setFixedSize(800,600);
    this->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存
    ui->tableViewStudent->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableViewStudent->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewStudent->setAlternatingRowColors(true);

    ui->actSubmit->setEnabled(false);
    ui->actRevert->setEnabled(false);
    ui->actRecAppend->setEnabled(false);
    ui->actRecDelete->setEnabled(false);
    ui->actRecInsert->setEnabled(false);

}

AdminWindow::~AdminWindow()
{
    delete ui;
}


void AdminWindow::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);

    ui->actSubmit->setEnabled(tabModelStudent->isDirty() |
                              tabModelAdmin->isDirty() |
                              tabModelCourse->isDirty() |
                              tabModelTeacher->isDirty());
    ui->actRevert->setEnabled(tabModelStudent->isDirty() |
                              tabModelAdmin->isDirty() |
                              tabModelCourse->isDirty() |
                              tabModelTeacher->isDirty());

}


//打开数据表
void AdminWindow::on_actOpenDB_triggered()
{
    db=QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName(DB_HOSTNAME);
    db.setDatabaseName(DB_NAME);
    db.setUserName(DB_USERNAME);
    db.setPassword(DB_PASSWORD);

    if(!db.open())
        QMessageBox::warning(this,"错误","打开数据库失败",QMessageBox::Ok,QMessageBox::NoButton);

    openTable();

}

void AdminWindow::openTable()
{
    //学生表
    tabModelStudent=new QSqlTableModel(this,db);
    tabModelStudent->setTable("student");
    tabModelStudent->setEditStrategy(QSqlTableModel::OnManualSubmit);
    if(!(tabModelStudent->select()))
    {
        QMessageBox::critical(this,"错误","打开数据表错误,错误信息\n"
                              +tabModelStudent->lastError().text(),QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    tabModelStudent->setHeaderData(tabModelStudent->fieldIndex("id"),Qt::Horizontal,"学号");
    tabModelStudent->setHeaderData(tabModelStudent->fieldIndex("name"),Qt::Horizontal,"姓名");
    tabModelStudent->setHeaderData(tabModelStudent->fieldIndex("class"),Qt::Horizontal,"班级");
    tabModelStudent->setHeaderData(tabModelStudent->fieldIndex("password"),Qt::Horizontal,"密码");

    theSelectionStudent=new QItemSelectionModel(tabModelStudent);

    ui->tableViewStudent->setModel(tabModelStudent);
    ui->tableViewStudent->setSelectionModel(theSelectionStudent);


    //课程表
    tabModelCourse=new QSqlTableModel(this,db);
    tabModelCourse->setTable("course");
    tabModelCourse->setEditStrategy(QSqlTableModel::OnManualSubmit);
    if(!(tabModelCourse->select()))
    {
        QMessageBox::critical(this,"错误","打开数据表错误,错误信息\n"
                              +tabModelCourse->lastError().text(),QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    tabModelCourse->setHeaderData(tabModelCourse->fieldIndex("id"),Qt::Horizontal,"课程号");
    tabModelCourse->setHeaderData(tabModelCourse->fieldIndex("name"),Qt::Horizontal,"课程名");
    tabModelCourse->setHeaderData(tabModelCourse->fieldIndex("teacher"),Qt::Horizontal,"任课老师");

    theSelectionCourse=new QItemSelectionModel(tabModelCourse);

    ui->tableViewCourse->setModel(tabModelCourse);
    ui->tableViewCourse->setSelectionModel(theSelectionCourse);

    //老师表
    tabModelTeacher=new QSqlTableModel(this,db);
    tabModelTeacher->setTable("teacher");
    tabModelTeacher->setEditStrategy(QSqlTableModel::OnManualSubmit);
    if(!(tabModelTeacher->select()))
    {
        QMessageBox::critical(this,"错误","打开数据表错误,错误信息\n"
                              +tabModelTeacher->lastError().text(),QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    tabModelTeacher->setHeaderData(tabModelTeacher->fieldIndex("id"),Qt::Horizontal,"老师号");
    tabModelTeacher->setHeaderData(tabModelTeacher->fieldIndex("name"),Qt::Horizontal,"姓名");
    tabModelTeacher->setHeaderData(tabModelTeacher->fieldIndex("password"),Qt::Horizontal,"密码");

    theSelectionTeacher=new QItemSelectionModel(tabModelTeacher);

    ui->tableViewTeacher->setModel(tabModelTeacher);
    ui->tableViewTeacher->setSelectionModel(theSelectionTeacher);

    //管理员表
    tabModelAdmin=new QSqlTableModel(this,db);
    tabModelAdmin->setTable("admin");
    tabModelAdmin->setEditStrategy(QSqlTableModel::OnManualSubmit);
    if(!(tabModelAdmin->select()))
    {
        QMessageBox::critical(this,"错误","打开数据表错误,错误信息\n"
                              +tabModelAdmin->lastError().text(),QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    tabModelAdmin->setHeaderData(tabModelAdmin->fieldIndex("id"),Qt::Horizontal,"管理员号");
    tabModelAdmin->setHeaderData(tabModelAdmin->fieldIndex("password"),Qt::Horizontal,"密码");

    theSelectionAdmin=new QItemSelectionModel(tabModelAdmin);

    ui->tableViewAdmin->setModel(tabModelAdmin);
    ui->tableViewAdmin->setSelectionModel(theSelectionAdmin);



    //信号和槽函数关联
    connect(theSelectionStudent,SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));

    connect(theSelectionTeacher,SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));

    connect(theSelectionCourse,SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));

    connect(theSelectionAdmin,SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));


    //
    ui->actSubmit->setEnabled(false);
    ui->actRevert->setEnabled(false);
    ui->actRecAppend->setEnabled(true);
    ui->actRecDelete->setEnabled(true);
    ui->actRecInsert->setEnabled(true);
}


//退出
void AdminWindow::on_actQuit_triggered()
{
    this->close();
}


//添加
void AdminWindow::on_actRecAppend_triggered()
{
    switch (ui->tabWidget->currentIndex())
    {
    case 0:
        tabModelStudent->insertRow(tabModelStudent->rowCount(),QModelIndex());
//      QModelIndex curIndexStudent=tabModelStudent->index(tabModelStudent->rowCount()-1,1);
//      theSelectionStudent->clearSelection();
//      theSelectionStudent->setCurrentIndex(curIndexStudent,QItemSelectionModel::Select);
        break;
    case 1:
        tabModelTeacher->insertRow(tabModelTeacher->rowCount(),QModelIndex());
        break;
    case 2:
        tabModelCourse->insertRow(tabModelCourse->rowCount(),QModelIndex());
        break;
    case 3:
        tabModelAdmin->insertRow(tabModelAdmin->rowCount(),QModelIndex());
        break;
    }


    ui->actSubmit->setEnabled(true);
    ui->actRevert->setEnabled(true);
}


void AdminWindow::on_actRecDelete_triggered()
{
    switch (ui->tabWidget->currentIndex())
    {
    case 0:
        tabModelStudent->removeRow(theSelectionStudent->currentIndex().row());
        break;
    case 1:
        tabModelTeacher->removeRow(theSelectionTeacher->currentIndex().row());
        break;
    case 2:
        tabModelCourse->removeRow(theSelectionCourse->currentIndex().row());
        break;
    case 3:
        tabModelAdmin->removeRow(theSelectionAdmin->currentIndex().row());
        break;
    }



    ui->actSubmit->setEnabled(true);
    ui->actRevert->setEnabled(true);
}


void AdminWindow::on_actRecInsert_triggered()
{
    switch (ui->tabWidget->currentIndex())
    {
    case 0:
        tabModelStudent->insertRow(ui->tableViewStudent->currentIndex().row());
        break;
    case 1:
        tabModelTeacher->insertRow(ui->tableViewTeacher->currentIndex().row());
        break;
    case 2:
        tabModelCourse->insertRow(ui->tableViewCourse->currentIndex().row());
        break;
    case 3:
        tabModelAdmin->insertRow(ui->tableViewAdmin->currentIndex().row());
        break;
    }


    ui->actSubmit->setEnabled(true);
    ui->actRevert->setEnabled(true);
}

void AdminWindow::on_actSubmit_triggered()
{
    bool res=tabModelStudent->submitAll() | tabModelAdmin->submitAll() | tabModelCourse->submitAll() | tabModelTeacher->submitAll();
    if(!res)
    {
        QMessageBox::information(this,"消息","数据保存错误,错误信息\n"
                                 +tabModelStudent->lastError().text(),QMessageBox::Ok,QMessageBox::NoButton);
    }
    else
    {
        QMessageBox::information(this,"消息","保存成功",QMessageBox::Ok,QMessageBox::NoButton);

        ui->actSubmit->setEnabled(false);
        ui->actRevert->setEnabled(false);
    }
}



void AdminWindow::on_actRevert_triggered()
{
    switch (ui->tabWidget->currentIndex())
    {
    case 0:
        tabModelStudent->revertAll();
        break;
    case 1:
        tabModelTeacher->revertAll();
        break;
    case 2:
        tabModelCourse->revertAll();
        break;
    case 3:
        tabModelTeacher->revertAll();
        break;

    }

    ui->actSubmit->setEnabled(false);
    ui->actRevert->setEnabled(false);
}
