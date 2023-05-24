#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->client = SingClient::getInstance();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_auth_clicked()
{
    QString login = ui->login->text();
    QString password = ui->pass->text();
    if (reg(login, password) == 1){
        QMessageBox::information(this, "Уведомление", "Авторизация прошла успешно");
        close();
    } else {
        QMessageBox::warning(this, "Уведомление", "Вы не авторизировались, попробуйте еще раз");
    }
}

bool MainWindow::reg (QString log, QString pass){

}

void MainWindow::on_reg_clicked()
{

}


void MainWindow::on_get_stats_clicked()
{
    client->sendToServer("get_stats ");

}
