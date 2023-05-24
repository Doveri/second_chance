#ifndef FUN_H
#define FUN_H
#include "consoleclientt.h"

#include <QString>
#include <QtWidgets/QWidget>

/**
 * @brief client переменая для инициализации клиента во всех окнах
 */
extern const SingClient * client;
/**
 * @brief login переменая для сохранения логина
 */
extern QString login;

#endif // FUN_H
