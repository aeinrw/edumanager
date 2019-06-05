#include "stuwindows.h"
#include "ui_stuwindows.h"

StuWindows::StuWindows(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StuWindows)
{
    ui->setupUi(this);

    this->setFixedSize(800,600);

    ui->tableViewStudent->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableViewStudent->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewStudent->setAlternatingRowColors(true);
}

StuWindows::~StuWindows()
{
    delete ui;
}

void StuWindows::on_actOpenDB_triggered()
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

void StuWindows::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);

    ui->actSubmit->setEnabled(tabModel->isDirty());
    ui->actRevert->setEnabled(tabModel->isDirty());

}

void StuWindows::on_currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);

    ui->actRecDelete->setEnabled(current.isValid());
}

void StuWindows::openTable()
{
    tabModel=new QSqlTableModel(this,db);
    tabModel->setTable("student");  //暂且只打开一个表,其他表日后在实现
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    if(!(tabModel->select()))
    {
        QMessageBox::critical(this,"错误","打开数据表错误,错误信息\n"
                              +tabModel->lastError().text(),QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }
    tabModel->setHeaderData(tabModel->fieldIndex("id"),Qt::Horizontal,"学号");
    tabModel->setHeaderData(tabModel->fieldIndex("name"),Qt::Horizontal,"姓名");
    tabModel->setHeaderData(tabModel->fieldIndex("class"),Qt::Horizontal,"班级");
    tabModel->setHeaderData(tabModel->fieldIndex("password"),Qt::Horizontal,"密码");

    theSelection=new QItemSelectionModel(tabModel);

    ui->tableViewStudent->setModel(tabModel);
    ui->tableViewStudent->setSelectionModel(theSelection);
}



void StuWindows::on_actQuit_triggered()
{
    this->close();
}



void StuWindows::on_actRecAppend_triggered()
{
    tabModel->insertRow(tabModel->rowCount(),QModelIndex());
    QModelIndex curIndex=tabModel->index(tabModel->rowCount()-1,1);
    theSelection->clearSelection();
    theSelection->setCurrentIndex(curIndex,QItemSelectionModel::Select);
}


void StuWindows::on_actRecDelete_triggered()
{
    QModelIndex curIndex=theSelection->currentIndex();
    tabModel->removeRow(curIndex.row());
}


void StuWindows::on_actRecInsert_triggered()
{
    QModelIndex curIndex=ui->tableViewStudent->currentIndex();
    tabModel->insertRow(curIndex.row());
    //theSelection->clearSelection();
    //theSelection->setCurrentIndex(curIndex,QItemSelectionModel::Select);
}

void StuWindows::on_actSubmit_triggered()
{
    bool res=tabModel->submitAll();
    if(!res)
    {
        QMessageBox::information(this,"消息","数据保存错误,错误信息\n"
                                 +tabModel->lastError().text(),QMessageBox::Ok,QMessageBox::NoButton);
    }
    else
    {
        QMessageBox::information(this,"消息","保存成功",QMessageBox::Ok,QMessageBox::NoButton);

        ui->actSubmit->setEnabled(false);
        ui->actRevert->setEnabled(false);
    }
}



void StuWindows::on_actRevert_triggered()
{
    tabModel->revertAll();
    ui->actSubmit->setEnabled(false);
    ui->actRevert->setEnabled(false);
}
