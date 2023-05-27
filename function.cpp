#include "function.h"

// Метод для обработки запросов
QString parsing(QString request)
{
    // Распарсиваем запрос на команду и параметры
    QStringList parts = request.split(" ");
    QString command = parts[0];
    QString response = "";

    // Обрабатываем различные команды
    if (command == "reg") {
        // Получаем логин и пароль пользователя из параметров команды
        QString login = parts[1];
        QString password = parts[2];

        // Регистрируем пользователя в базе данных и отправляем ответ клиенту
        if (registerUser(login, password)) {
            response = "User successfully registered!";
        } else {
            response = "Error registering user!";
        }
    } else if (command == "auth") {
        // Получаем логин и пароль пользователя из параметров команды
        QString login = parts[1];
        QString password = parts[2];

        // Авторизуем пользователя и отправляем ответ клиенту
        if (authUser(login, password)) {
            response = "User successfully authorized!";
        } else {
            response = "Error authorizing user!";
        }
    } else if (command == "get_users") {
        // Получаем логин и пароль пользователя из параметров команды
        QString login = parts[1];
        QString password = parts[2];

        // Если пользователь авторизован, получаем список всех пользователей и отправляем его клиенту
        if (authUser(login, password)) {
            QStringList users = getUsers();
            response = "Users: " + users.join(", ");
        } else {
            response = "You are not authorized!";
        }
    } else if (command == "get_stat") {
        // Получаем логин и пароль пользователя из параметров команды
        QString login = parts[1];
        QString password = parts[2];

        // Если пользователь авторизован, получаем статистику и отправляем ее клиенту
        if (authUser(login, password)) {
            QStringList stat = getStat();
            response = "Stat: " + stat.join(", ");
        } else {
            response = "You are not authorized!";
        }
    } else if (command == "clean_db") {
        // Очищаем базу данных и отправляем ответ клиенту
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

// Метод для регистрации нового пользователя в базе данных
bool registerUser(QString login, QString password)
{
    // Получаем объект класса Singleton для работы с базой данных
    Singleton& db = Singleton::getInstance();

    // Подготавливаем запрос на добавление пользователя в базу данных
    QSqlQuery q(db.db);
    q.prepare("INSERT INTO users (login, password) VALUES (:login, :password)");
    q.bindValue(":login", login);
    q.bindValue(":password", password);

    // Выполняем запрос и проверяем его результат
    if (!q.exec()) {
        qDebug() << "Error registering user!";
        qDebug() << q.lastError().text();
        return false;
    }

    return true;
}

// Метод для авторизации пользователя в базе данных
bool authUser(QString login, QString password)
{
    // Получаем объект класса Singleton для работы с базой данных
    Singleton& db = Singleton::getInstance();

    // Подготавливаем запрос на поиск пользователя в базе данных
    QSqlQuery q(db.db);
    q.prepare("SELECT * FROM users WHERE login = :login AND password = :password");
    q.bindValue(":login", login);
    q.bindValue(":password", password);

    // Выполняем запрос и проверяем его результат
    if (q.exec() && q.first()) {
        return true;
    }
    return false;
}

// Метод для получения списка всех пользователей из базы данных
QStringList getUsers()
{
    // Получаем объект класса Singleton для работы с базой данных
    Singleton& db = Singleton::getInstance();

    // Подготавливаем запрос на выборку всех пользователей из базы данных
    QSqlQuery q(db.db);
    QStringList users;
    if (!q.exec("SELECT login FROM users")) {
        qDebug() << "Error selecting users!";
        qDebug() << q.lastError().text();
    }

    // Получаем список всех пользователей из результата запроса
    while (q.next()) {
        users.append(q.value(0).toString());
    }

    return users;
}

// Метод для получения статистики из базы данных
QStringList getStat()
{
    // Получаем объект класса Singleton для работы с базой данных
    Singleton& db = Singleton::getInstance();
    // Подготавливаем запрос на выборку статистики из базы данных
    QSqlQuery q(db.db);
    QStringList stat;
    if (!q.exec("SELECT * FROM demo")) {
        qDebug() << "Error selecting stat!";
        qDebug() << q.lastError().text();
    }

    // Получаем список статистики из результата запроса
    while (q.next()) {
        stat.append(q.value(0).toString());
    }

    return stat;
}

// Метод для очистки базы данных
bool cleanDatabase()
{
    // Получаем объект класса Singleton для работы с базой данных
    Singleton& db = Singleton::getInstance();

    // Подготавливаем запрос на удаление всех пользователей из базы данных
    QSqlQuery q(db.db);
    if (!q.exec("DELETE FROM users")) {
        qDebug() << "Error cleaning database!";
        qDebug() << q.lastError().text();
        return false;
    }
    return true;
}


QVector<QPair<int, int>> getRandomEdges(int n)
{
    QVector<QPair<int, int>> edges;
    QSet<QPair<int, int>> edgeSet;

    while (edges.size() < n)
    {
        int u = rand() % 10;
        int v = rand() % 10;
        QPair<int, int> edge(u, v);

        if (!edgeSet.contains(edge))
        {
            edges.append(edge);
            edgeSet.insert(edge);
        }
    }

    return edges;
}


QVector<int> getRandomPruferCode()
{
    QVector<int> pruferCode;

    for (int i = 0; i < 7; i++)
    {
        int num = rand() % 10;
        pruferCode.append(num);
    }

    return pruferCode;
}


QVector<int> pruferCode(QVector<QPair<int,int>> edges)
{
    QVector<int> pruf_code;
    while (edges.size() > 1)
    {
        QHash <int, int> counts;
        for (const auto &edge :edges)
        {
            counts[edge.first]++;
            counts[edge.second]++;
        }
        QVector<int> leaf;
        for (auto it = counts.begin(); it != counts.end(); ++it) {
            int number = it.key();
            int count = it.value();
            if (count == 1) {
                leaf.push_back(number);
            }
        }
        int minIndex = leaf.indexOf(*std::min_element(leaf.begin(), leaf.end()));
        int min_leaf = leaf[minIndex];

        int index_to_remove = -1;
        for (int i = 0; i < edges.size(); i++)
        {
            if (edges[i].first == min_leaf)
            {
                pruf_code.push_back(edges[i].second);
                index_to_remove = i;
                break;
            }
            if (edges[i].second == min_leaf)
            {
                pruf_code.push_back(edges[i].first);
                index_to_remove = i;
                break;
            }
        }
        if (index_to_remove != -1)
        {
            edges.erase(edges.begin() + index_to_remove);
        }

    }

    return pruf_code;
}

QVector<QPair<int,int>> pruferDecode(QVector<int> c)
{
    QVector<QPair<int,int>> nodes;

    QVector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    while (!c.empty())
    {
        QVector<int> remain_elements;
        int min_element;
        for (int i = 0; i < v.size(); i++)
        {
            // Если элемент не найден в векторе `c`, добавляем его в `remain_elements`.
            if (std::find(c.begin(), c.end(), v[i]) == c.end())
            {
                remain_elements.push_back(v[i]);
            }
        }
        int min_index = remain_elements.indexOf(*std::min_element(remain_elements.begin(), remain_elements.end()));
        min_element = remain_elements[min_index];

        int first_c_element = c.front();
        nodes.push_back(qMakePair(min_element, first_c_element));
        c.removeFirst();
        v.remove(min_index);
        remain_elements.clear();
    }
    nodes.push_back({v[0], v[1]});

    return nodes;
}

