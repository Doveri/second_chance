#ifndef SINGLETON_H
#define SINGLETON_H

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>

class Singleton
{
public:
    static Singleton& getInstance();

    bool connectToDB();
    void close();
    QSqlDatabase db;
private:
    Singleton();
    Singleton(Singleton const&);
    void operator=(Singleton const&);


};

#endif // SINGLETON_H

//Реализация singleton паттерна позволяет:

//Получить доступ к единственному экземпляру класса через метод getInstance
//Подключиться к БД через метод connectToDB
//Закрыть соединение с БД через метод close
//Сделать класс singleton, запрещая копирование и присваивание экземпляра
//Этот класс может использоваться для удобного подключения к БД из любой части программы.

//Такая полная реализация паттерна singleton позволяет грамотно организовать работу с БД в приложении.
