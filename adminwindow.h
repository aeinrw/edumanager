#ifndef STUWINDOWS_H
#define STUWINDOWS_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QMessageBox>

#include "globle.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

private slots:
    void on_currentChanged(const QModelIndex &current,const QModelIndex &previous);

    void on_actOpenDB_triggered();

    void on_actQuit_triggered();

    void on_actRecAppend_triggered();

    void on_actRecDelete_triggered();

    void on_actRecInsert_triggered();

    void on_actSubmit_triggered();

    void on_actRevert_triggered();

private:
    Ui::AdminWindow *ui;
    QSqlDatabase db;

    QSqlTableModel *tabModelStudent;
    QItemSelectionModel *theSelectionStudent;

    QSqlTableModel *tabModelTeacher;
    QItemSelectionModel *theSelectionTeacher;

    QSqlTableModel *tabModelCourse;
    QItemSelectionModel *theSelectionCourse;

    QSqlTableModel *tabModelAdmin;
    QItemSelectionModel *theSelectionAdmin;

    void openTable();
    void getFieldNames();

};

#endif // STUWINDOWS_H










