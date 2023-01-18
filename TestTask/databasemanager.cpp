#include <QFileInfo>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "databasemanager.h"

DataBaseManager::DataBaseManager()
{
    connect_data_base();
}

DataBaseManager *DataBaseManager::get_instance()
{
    static DataBaseManager instance;
    return &instance;
}

QSqlDatabase DataBaseManager::get_data_base()
{
    return QSqlDatabase::database(string_data_base_name);
}


bool DataBaseManager::connect_data_base()
{
    bool bool_success = false;
    if(!QFileInfo::exists(QString("E:/Reestr/inventory.db"))) //Проверка существования файла БД
    {
        QMessageBox::critical(Q_NULLPTR, QString("Сообщение об ошибке!"),
        QString("Не обнаружена база данных!"));
        return bool_success;
    }

    // Подключение и настройка БД, помещение наименованиz БД в поле класса
    QSqlDatabase sql_data_base = QSqlDatabase::addDatabase(QString("QSQLITE"), QString("E:/Reestr/inventory.db"));
    sql_data_base.setConnectOptions("QSQLITE_OPEN_URI");
    sql_data_base.setDatabaseName(QString("E:/Reestr/inventory.db"));

    if(!sql_data_base.open())
    {
        qDebug() << "Не удалось подключиться к базе данных: "
                 << sql_data_base.databaseName();
        return bool_success;
    }

    string_data_base_name = sql_data_base.databaseName();
    QSqlQuery sql_query(sql_data_base);

    bool_success = sql_query.exec(QString("PRAGMA foreign_keys = on"));
    if(!sql_query.isActive())
    {
        qDebug() << "Не удалось выполнить запрос к базе данных: "
                 << sql_data_base.databaseName()
                 << QChar('\n')
                 << "Query: "
                 << sql_query.lastQuery()
                 << QChar('\n')
                 << "Сообщение драйвера базы данных: "
                 << sql_query.lastError();
    }
    return bool_success;
}

