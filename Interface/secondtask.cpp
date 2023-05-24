#include "secondtask.h"
#include "ui_secondtask.h"

QString gettask(int n)
{
    return "task " + QString::number(n);
}

QString getvariant(int n)
{
    return "variant " + QString::number(n);
}


SecondTask::SecondTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondTask)
{
    ui->setupUi(this);
}

SecondTask::~SecondTask()
{
    delete ui;
}

void SecondTask::on_SendAns_clicked()
{
    close();
}

void SecondTask::setTaskNumber(int n)
{
    task_number=n;
    ui->label->setText(gettask(n) + getvariant(n));
    this->show();
}

