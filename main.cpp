#include <QCoreApplication>
#include "mytcpserver.h"

// Это главная функция программы
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Создаем объект класса MyTcpServer
    MyTcpServer server;

    // Запускаем цикл обработки событий приложения
    return a.exec();
}
