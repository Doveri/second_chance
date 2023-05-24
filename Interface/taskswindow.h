#ifndef TASKSWINDOW_H
#define TASKSWINDOW_H

#include <QDialog>

namespace Ui {
class tasksWindow;
}

class tasksWindow : public QDialog
{
    Q_OBJECT

public:
    explicit tasksWindow(QWidget *parent = nullptr);
    ~tasksWindow();

private slots:
    void on_FirstTask_clicked();

private:
    Ui::tasksWindow *ui;
};

#endif // TASKSWINDOW_H
