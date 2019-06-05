#ifndef STUWINDOWS_H
#define STUWINDOWS_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include "globle.h"
#include <QMessageBox>

namespace Ui {
class StuWindows;
}

class StuWindows : public QMainWindow
{
    Q_OBJECT

public:
    explicit StuWindows(QWidget *parent = nullptr);
    ~StuWindows();

private slots:
    void on_actOpenDB_triggered();
    void on_currentChanged(const QModelIndex &current,const QModelIndex &previous);
    void on_currentRowChanged(const QModelIndex &current,const QModelIndex &previous);

    void on_actQuit_triggered();

    void on_actRecAppend_triggered();

    void on_actRecDelete_triggered();

    void on_actRecInsert_triggered();

    void on_actSubmit_triggered();

    void on_actRevert_triggered();

private:
    Ui::StuWindows *ui;
    QSqlDatabase db;
    QSqlTableModel *tabModel;
    QItemSelectionModel *theSelection;

    void openTable();
    void getFieldNames();

};

#endif // STUWINDOWS_H










