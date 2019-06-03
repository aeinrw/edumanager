#ifndef STUWINDOWS_H
#define STUWINDOWS_H

#include <QMainWindow>

namespace Ui {
class StuWindows;
}

class StuWindows : public QMainWindow
{
    Q_OBJECT

public:
    explicit StuWindows(QWidget *parent = nullptr);
    ~StuWindows();

private:
    Ui::StuWindows *ui;
};

#endif // STUWINDOWS_H
