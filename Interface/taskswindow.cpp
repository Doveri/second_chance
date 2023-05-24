#include "taskswindow.h"
#include "ui_taskswindow.h"

tasksWindow::tasksWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tasksWindow)
{
    ui->setupUi(this);
}

tasksWindow::~tasksWindow()
{
    delete ui;
}

void tasksWindow::on_FirstTask_clicked()
{

}

