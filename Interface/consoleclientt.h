#ifndef CONSOLECLIENTT_H
#define CONSOLECLIENTT_H

#include <QTcpSocket>
#include <QDebug>
#include <QtNetwork>
#include <QObject>

class SingClient;

class SingClientDestroyer{
    private:
        SingClient * p_instance;
    public:
        ~SingClientDestroyer() { delete p_instance;}
        void initialize(SingClient * p){p_instance = p;}
};


class SingClient : public QObject
{
    Q_OBJECT
private:
        static SingClient * p_instance;
        static SingClientDestroyer destroyer;
        QTcpSocket* socket;
        QString Message;
    protected:
        explicit SingClient();
        SingClient(const SingClient& ) = delete ;
        SingClient& operator = (SingClient &) = delete;
        ~SingClient();
        friend class SingClientDestroyer;
    public:
        static SingClient* getInstance();
        QString sendToServer(const QString&);
    protected slots:
        void slot_readFromServer();
    signals:
};

#endif // CONSOLECLIENTT_H
