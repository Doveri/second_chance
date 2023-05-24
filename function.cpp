#include "function.h"
#include "singleton.h"

QString parsing(QString request)
{
    QStringList parts = request.split(" ");
    QString command = parts[0];
    QString response;

    if (command == "reg") {
        QString login = parts[1];
        QString password = parts[2];
        if (registerUser(login, password)) {
            response = "User successfully registered!";
        } else {
            response = "Error registering user!";
        }
    } else if (command == "auth") {
        QString login = parts[1];
        QString password = parts[2];
        if (authUser(login, password)) {
            response = "User successfully authorized!";
        } else {
            response = "Error authorizing user!";
        }
    } else if (command == "get_users") {
        QString login = parts[1];
        QString password = parts[2];
        if (authUser(login, password)) {
            QStringList users = getUsers();
            response = "Users: " + users.join(", ");
        } else {
            response = "You are not authorized!";
        }
    } else if (command == "clean_db") {
        if (cleanDatabase()) {
            response = "Database cleaned successfully!";
        } else {
            response = "Error cleaning database!";
        }
    } else {
        response = "Unknown command!";
    }

    return response;
}

bool registerUser(QString login, QString password)
{
    Singleton& db = Singleton::getInstance();
    QSqlQuery q;
    q.prepare("INSERT INTO users (login, password) VALUES (:login, :password)");
    q.bindValue(":login", login);
    q.bindValue(":password", password);
    if (!q.exec()) {
        qDebug() << "Error registering user!";
        qDebug() << q.lastError().text();
    }
    return q.exec();
}

bool authUser(QString login, QString password)
{
    Singleton& db = Singleton::getInstance();
    QSqlQuery q;
    q.prepare("SELECT * FROM users WHERE login = :login AND password = :password");
    q.bindValue(":login", login);
    q.bindValue(":password", password);
    if (q.exec() && q.first()) {
        return true;
    }
    return false;
}

QStringList getUsers()
{
    Singleton& db = Singleton::getInstance();
    QSqlQuery query;
    QStringList users;
    if (!query.exec("SELECT login FROM users")) {
        qDebug() << "Error selecting users!";
        qDebug() << query.lastError().text();
    }
    while (query.next()) {
        users.append(query.value(0).toString());
    }
    return users;
}

bool cleanDatabase()
{
    Singleton& db = Singleton::getInstance();
    QSqlQuery q;
    if (!q.exec("DELETE FROM users")) {
        qDebug() << "Error cleaning database!";
        qDebug() << q.lastError().text();
        return false;
    }
    return true;
}


//QVector<int> pruferCode(QVector<QPair<int,int>> edges)
//{
//    QVector<int> pruf_code;
//    while (edges.size() > 1)
//    {
//        QHash <int, int> counts;
//        for (const auto &edge :edges)
//        {
//            counts[edge.first]++;
//            counts[edge.second]++;
//        }
//        QVector<int> leaf;
//        for (auto it = counts.begin(); it != counts.end(); ++it) {
//            int number = it.key();
//            int count = it.value();
//            if (count == 1) {
//                leaf.push_back(number);
//            }
//        }
//        int min_leaf = qMinElement(leaf.begin(), leaf.end());

//        int index_to_remove = -1;
//        for (int i = 0; i < edges.size(); i++)
//                {
//                    if (edges[i].first == min_leaf)
//                    {
//                        pruf_code.push_back(edges[i].second);
//                        index_to_remove = i;
//                        break;
//                    }
//                    if (edges[i].second == min_leaf)
//                    {
//                        pruf_code.push_back(edges[i].first);
//                        index_to_remove = i;
//                        break;
//                    }
//                }
//        if (index_to_remove != -1)
//            {
//                edges.erase(edges.begin() + index_to_remove);
//            }

//    }

//    return pruf_code;
//}

//QVector<QPair<int,int>> pruferDecode(QVector<int> c)
//{
//    QVector<QPair<int,int>> nodes;

//    QVector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};

//    while (!c.empty())
//    {
//        QVector<int> remain_elements;
//        int min_element;
//        for (int i = 0; i < v.size(); i++)
//                {
//                    // Если элемент не найден в векторе `c`, добавляем его в `remain_elements`.
//                    if (std::find(c.begin(), c.end(), v[i]) == c.end())
//                    {
//                        remain_elements.push_back(v[i]);
//                    }
//                }
//        min_element = qMinElement(remain_elements.begin(), remain_elements.end());

//        int first_c_element = c.front();
//        nodes.push_back(qMakePair(min_element, first_c_element));
//        c.erase(c.begin());                                             // Удаляем первый элемент из вектора `c`.
//        v.erase(remove(v.begin(), v.end(), min_element), v.end());
//        remain_elements.clear();
//    }
//    nodes.push_back({v[0], v[1]});

//    return nodes;
//}

