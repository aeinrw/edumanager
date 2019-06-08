#include "studentwindow.h"
#include "ui_studentwindow.h"

StudentWindow::StudentWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("学生面板");
    this->setFixedSize(800,600);
    this->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存


}

StudentWindow::~StudentWindow()
{
    delete ui;
}
