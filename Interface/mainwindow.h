#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "secondtask.h"
#include <QMainWindow>
#include "consoleclientt.h"
#include "func.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    SingClient* client;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_auth_clicked();

    void on_reg_clicked();

    void on_get_stats_clicked();

private:
    bool reg(QString, QString);
    Ui::MainWindow *ui;
    SecondTask *window;

};
#endif // MAINWINDOW_H
