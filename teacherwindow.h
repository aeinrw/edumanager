#ifndef TEACHERWINDOW_H
#define TEACHERWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "globle.h"
#include <QtSql>
#include <QMessageBox>
#include <QDataWidgetMapper>

namespace Ui {
class TeacherWindow;
}

class TeacherWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TeacherWindow(QWidget *parent = nullptr);
    ~TeacherWindow();



private slots:
    void on_pushButton_clicked();

private:
    Ui::TeacherWindow *ui;
    QSqlDatabase db;
    void openTable();
};

#endif // TEACHERWINDOW_H
