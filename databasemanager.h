#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QList>
#include <QSqlDatabase>
#include <QTemporaryFile>

  //Менеджер управления подкючения к базе данных.
class DataBaseManager
{
public:
    //Статический метод возвращает указатель на локальный статический экземпляр класса
    static DataBaseManager *get_instance();

    //Метод возвращает подлючение к текущей базе данных
    QSqlDatabase get_data_base();

private:
    //Паттерн проектирования Singleton
    //Приватный конструктор используется для контроля над количеством создаваемых экземпляров
    //Всегда можно будет создать только один объект

    DataBaseManager();
    //Запрет копирования и перемещения
    Q_DISABLE_COPY(DataBaseManager)
    DataBaseManager(DataBaseManager&&) = delete;
    DataBaseManager& operator=(DataBaseManager&&) = delete;

    //Подключение к существующей базе данных
    bool connect_data_base();

    //Поле содержит наименование текущей подключенной БД
    QString string_data_base_name;
};

#endif // DATABASEMANAGER_H
