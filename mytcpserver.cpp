#include "mytcpserver.h"
#include "singleton.h"
#include "function.h"

MyTcpServer::MyTcpServer(QObject *parent) : QTcpServer(parent)
{
    if (!listen(QHostAddress::Any, 33333)) {
        qDebug() << "Server not started!";
        return;
    }
    qDebug() << "Server started!";
    connect(this, &MyTcpServer::newConnection, this, &MyTcpServer::slotNewConnection);
    connectToDatabase();
}

void MyTcpServer::sendToClient(QString message)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << quint16(0) << message;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    clientSocket->write(block);
}

void MyTcpServer::slotNewConnection()
{
    qDebug() << "New user connected!";
    clientSocket = nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
}

void MyTcpServer::slotClientDisconnected()
{
    qDebug() << "User disconnected!";
    clientSocket->deleteLater();
}

void MyTcpServer::slotServerRead()
{
    if (!clientSocket->canReadLine()) return;
    QString request = clientSocket->readLine().trimmed();
    qDebug() << "Request received: " << request;

    QString response = parsing(request);
    sendToClient(response);
}

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

void MyTcpServer::connectToDatabase()
{
    Singleton& db = Singleton::getInstance();
    if (!db.connectToDB()) {
        qDebug() << "Failed to connect to database!";
    }
}

void MyTcpServer::close()
{
    Singleton& db = Singleton::getInstance();
    db.close();  // Закрываем соединение с БД
    qDebug() << "Connection to database closed!";
}
