#ifndef FUNCTION_H
#define FUNCTION_H

#include <QSqlQuery>
#include <QSqlError>
#include <QVector>
#include <QPair>
#include <QHash>
#include <QtAlgorithms>
#include <algorithm>

QString parsing(QString request);
bool registerUser(QString login, QString password);
bool authUser(QString login, QString password);
bool cleanDatabase();
QStringList getUsers();
QVector<int> pruferCode(QVector<QPair<int,int>> edges);
QVector<QPair<int,int>> pruferDecode(QVector<int> c);



#endif // FUNCTION_H

//Эти файлы реализуют следующие функции:

//parsing - разбор запроса и выполнение соответствующих действий (регистрация, авторизация, получение пользователей)
//registerUser - регистрация нового пользователя в БД
//authUser - авторизация пользователя
//getUsers - получение списка пользователей для авторизованного пользователя
//Для удобства работы с БД используется singleton.

//Эти функции позволяют реализовать основную бизнес-логику сервера - регистрацию и авторизацию пользователей, получение данных из БД.
