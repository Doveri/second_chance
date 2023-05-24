#include "singleton.h"

Singleton& Singleton::getInstance()
{
    static Singleton instance;
    return instance;
}

bool Singleton::connectToDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    if (!db.open()) {
        qDebug() << "Database not connected!";
        qDebug() << db.lastError().text();
        return false;
    }
    qDebug() << "Database connected!";
    return true;
}

void Singleton::close()
{
    db.close();
    qDebug() << "Connection to database closed!";
}

Singleton::Singleton() {}

Singleton::Singleton(Singleton const&)  {}

void Singleton::operator=(Singleton const&)  {}
