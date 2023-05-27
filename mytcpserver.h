#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

#include "singleton.h"
#include "function.h"

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);

private slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotReadClient();
    void slotServerRead();
    void connectToDatabase();
    void sendToClient(QString message);
    void close();

private:
    QTcpSocket* clientSocket;
};

#endif // MYTCPSERVER_H

//Этот файл реализует следующее:

//Конструктор сервера, запускающий его на порту 8080
//Обработчик нового подключения (slotNewConnection), сохраняющий сокет клиента и подключающий сигналы
//Обработчик отключения клиента (slotClientDisconnected), удаляющий сокет
//Обработчик чтения данных от сервера (slotServerRead), разбирающий запрос и вызывающий функцию parsing для его обработки
//Обработчик чтения данных от клиента (slotReadClient), аналогичный предыдущему но для запросов от клиента
//Метод connectToDatabase для подключения к БД через singleton
//Этот класс позволяет реализовать основную логику сервера - принимать подключения, читать запросы и обрабатывать их, подключаться к БД.
