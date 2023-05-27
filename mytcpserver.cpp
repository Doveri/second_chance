#include "mytcpserver.h"

// Конструктор класса MyTcpServer
MyTcpServer::MyTcpServer(QObject *parent) : QTcpServer(parent)
{
    // Запуск сервера на порту 33333 и вывод сообщения, если не удалось запустить сервер
    if (!listen(QHostAddress::Any, 33333)) {
        qDebug() << "Server not started!";
        return;
    }
    qDebug() << "Server started!";

    // Устанавливаем связь между сигналом newConnection и слотом slotNewConnection
    connect(this, &MyTcpServer::newConnection, this, &MyTcpServer::slotNewConnection);
    connectToDatabase();
}

// Метод для отправки сообщений клиенту
void MyTcpServer::sendToClient(QString message)
{
    // Создаем объект QByteArray и QDataStream и записываем сообщение в блок данных
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << quint16(0) << message;
    out.device()->seek(0);

    // Записываем размер блока в начало блока данных
    out << quint16(block.size() - sizeof(quint16));

    // Отправляем блок данных клиенту
    clientSocket->write(block);
}

// Слот, вызываемый при новом подключении клиента
void MyTcpServer::slotNewConnection()
{
    qDebug() << "New user connected!";

    // Получаем указатель на сокет клиента и устанавливаем связь между сигналами readyRead и disconnected и соответствующими слотами
    clientSocket = nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
}

// Слот, вызываемый при отключении клиента
void MyTcpServer::slotClientDisconnected()
{
    qDebug() << "User disconnected!";

    // Удаляем объект сокета клиента
    clientSocket->deleteLater();
}

// Слот, вызываемый при чтении данных от клиента
void MyTcpServer::slotServerRead()
{
    // Проверяем, можно ли прочитать строку из сокета
    if (!clientSocket->canReadLine()) return;

    // Читаем строку из сокета и выводим сообщение о запросе в консоль
    QString request = clientSocket->readLine().trimmed();
    qDebug() << "Request received: " << request;

    // Обрабатываем запрос и отправляем ответ клиенту
    QString response = parsing(request);
    sendToClient(response);
}

// Метод чтения данных от клиента, который не используется в данном коде
void MyTcpServer::slotReadClient()
{
    QString request;
    while (clientSocket->bytesAvailable()) {
        QByteArray data = clientSocket->readAll();
        request += QString::fromUtf8(data);
    }
    request = request.trimmed();
    qDebug() << "Request received: " << request;

    QString response = parsing(request);
    sendToClient(response);
}

// Метод для соединения с базой данных
void MyTcpServer::connectToDatabase()
{
    // Создаем объект класса Singleton и подключаемся к базе данных
    Singleton& db = Singleton::getInstance();
    if (!db.connectToDB()) {
        qDebug() << "Failed to connect to database!";
    }
}

// Метод для закрытия соединения с базой данных
void MyTcpServer::close()
{
    // Получаем объект класса Singleton и закрываем соединение с базой данных
    Singleton& db = Singleton::getInstance();
    db.close();  // Закрываем соединение с БД
    qDebug() << "Connection to database closed!";
}
