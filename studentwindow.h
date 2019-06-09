#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "globle.h"
#include <QtSql>
#include <QMessageBox>
#include <QDataWidgetMapper>


namespace Ui {
class StudentWindow;
}

class StudentWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentWindow(QWidget *parent = nullptr);
    ~StudentWindow();



private slots:
    void on_btnChange_clicked();

private:
    Ui::StudentWindow *ui;
    QSqlDatabase db;

    void openTable();
};

#endif // STUDENTWINDOW_H
