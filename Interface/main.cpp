#include "mainwindow.h"

#include <QApplication>
#include <QThread>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //registration s;
    //s.show();
    MainWindow q;
    q.show();
    return a.exec();
}
