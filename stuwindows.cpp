#include "stuwindows.h"
#include "ui_stuwindows.h"

StuWindows::StuWindows(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StuWindows)
{
    ui->setupUi(this);
}

StuWindows::~StuWindows()
{
    delete ui;
}
