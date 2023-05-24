#ifndef SECONDTASK_H
#define SECONDTASK_H

#include <QDialog>

namespace Ui {
class SecondTask;
}

class SecondTask : public QDialog
{
    Q_OBJECT

public:
    explicit SecondTask(QWidget *parent = nullptr);
    ~SecondTask();
    void setTaskNumber(int);

private slots:
    void on_SendAns_clicked();

private:
    Ui::SecondTask *ui;
    int task_number;
};

#endif // SECONDTASK_H
