#include "registration.h"
#include "ui_registration.h"
#include <QMessageBox>
registration::registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registration)
{
    ui->setupUi(this);
}

registration::~registration()
{
    delete ui;
}

void registration::on_pushButton_clicked()
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

bool registration::reg (QString log, QString pass){
    if (log == "111" && pass == "222"){
        return 1;
    } else {
        return 0;
    }
}
