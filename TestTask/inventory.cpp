#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "inventory.h"
#include "databasemanager.h"

bool Inventory::emplace_item_to_cell(
        int row,
        int column,
        int type,
        int count) {
    /**
      **************************************************************************

      **************************************************************************
    */
    bool bool_success = false;
    /**
      **************************************************************************

      **************************************************************************
    */
    QSqlDatabase sql_data_base =
            DataBaseManager::get_instance()->get_data_base();
    if(!sql_data_base.isOpen()) {
        qDebug() << "Отсутствует соединение с базой данных: "
                 << sql_data_base.databaseName();
        return bool_success;
    }
    /**
      **************************************************************************

      **************************************************************************
    */
    QSqlQuery sql_query(sql_data_base);

    sql_query.prepare(
                QString("INSERT "
                        "INTO inventory (row, column, item_key, count) "
                        "VALUES (:row, :column, :item_key, :count)"));

    sql_query.bindValue(0, row);
    sql_query.bindValue(1, column);
    sql_query.bindValue(2, type);
    sql_query.bindValue(3, count);

    bool_success = sql_query.exec();

    if(!sql_query.isActive())   {
        qDebug() << "Не удалось выполнить запрос к базе данных: "
                 << sql_data_base.databaseName()
                 << QChar('\n')
                 << "Query: "
                 << sql_query.lastQuery()
                 << QChar('\n')
                 << "Сообщение драйвера базы данных: "
                 << sql_query.lastError();
    }
    /**
      **************************************************************************

      **************************************************************************
    */
    return bool_success;
}
/**
  ******************************************************************************

  ******************************************************************************
*/
int Inventory::get_type_for_cell(
        int row,
        int column) const {
    /**
    **************************************************************************

    **************************************************************************
  */
    int int_result = -1;
    /**
    **************************************************************************

    **************************************************************************
  */
    QSqlDatabase sql_data_base =
            DataBaseManager::get_instance()->get_data_base();
    if(!sql_data_base.isOpen()) {
        qDebug() << "Отсутствует соединение с базой данных: "
                 << sql_data_base.databaseName();
        return int_result;
    }
    /**
      **************************************************************************

      **************************************************************************
    */
    QSqlQuery sql_query(sql_data_base);

    sql_query.prepare(
                QString("SELECT item_key "
                        "FROM inventory "
                        "WHERE row = :row AND column = :column"));

    sql_query.bindValue(0, row);
    sql_query.bindValue(1, column);

    sql_query.exec();

    if(!sql_query.isActive())   {
        qDebug() << "Не удалось выполнить запрос к базе данных: "
                 << sql_data_base.databaseName()
                 << QChar('\n')
                 << "Query: "
                 << sql_query.lastQuery()
                 << QChar('\n')
                 << "Сообщение драйвера базы данных: "
                 << sql_query.lastError();
    }
    else if(sql_query.first()) {
        int_result =
                sql_query.value(0).toInt();
    }
    /**
    **************************************************************************

    **************************************************************************
  */
    return int_result;
}
/**
  ******************************************************************************

  ******************************************************************************
*/
QString Inventory::get_image_for_cell(
        int row,
        int column) const {
    /**
      **************************************************************************

      **************************************************************************
    */
    QString string_result;
    /**
      **************************************************************************

      **************************************************************************
    */
    QSqlDatabase sql_data_base =
            DataBaseManager::get_instance()->get_data_base();
    if(!sql_data_base.isOpen()) {
        qDebug() << "Отсутствует соединение с базой данных: "
                 << sql_data_base.databaseName();
        return string_result;
    }
    /**
      **************************************************************************

      **************************************************************************
    */
    QSqlQuery sql_query(sql_data_base);

    sql_query.prepare(
                QString("SELECT image "
                        "FROM items "
                        "WHERE key = "
                        "(SELECT item_key "
                        "FROM inventory "
                        "WHERE row = :row AND column = :column)"));

    sql_query.bindValue(0, row);
    sql_query.bindValue(1, column);

    sql_query.exec();

    if(!sql_query.isActive())   {
        qDebug() << "Не удалось выполнить запрос к базе данных: "
                 << sql_data_base.databaseName()
                 << QChar('\n')
                 << "Query: "
                 << sql_query.lastQuery()
                 << QChar('\n')
                 << "Сообщение драйвера базы данных: "
                 << sql_query.lastError();
    }
    else if(sql_query.first()) {
        string_result =
                sql_query.value(0).toString();
    }
    /**
      **************************************************************************

      **************************************************************************
    */
    return string_result;
}
/**
  ******************************************************************************

  ******************************************************************************
*/
int Inventory::get_count_for_cell(
        int row,
        int column) const {
    /**
    **************************************************************************

    **************************************************************************
  */
    int int_result = 0;
    /**
    **************************************************************************

    **************************************************************************
  */
    QSqlDatabase sql_data_base =
            DataBaseManager::get_instance()->get_data_base();
    if(!sql_data_base.isOpen()) {
        qDebug() << "Отсутствует соединение с базой данных: "
                 << sql_data_base.databaseName();
        return int_result;
    }
    /**
      **************************************************************************

      **************************************************************************
    */
    QSqlQuery sql_query(sql_data_base);

    sql_query.prepare(
                QString("SELECT count "
                        "FROM inventory "
                        "WHERE row = :row AND column = :column"));

    sql_query.bindValue(0, row);
    sql_query.bindValue(1, column);

    sql_query.exec();

    if(!sql_query.isActive())   {
        qDebug() << "Не удалось выполнить запрос к базе данных: "
                 << sql_data_base.databaseName()
                 << QChar('\n')
                 << "Query: "
                 << sql_query.lastQuery()
                 << QChar('\n')
                 << "Сообщение драйвера базы данных: "
                 << sql_query.lastError();
    }
    else if(sql_query.first()) {
        int_result =
                sql_query.value(0).toInt();
    }
    /**
    **************************************************************************

    **************************************************************************
  */
    return int_result;
}
/**
  ******************************************************************************

  ******************************************************************************
*/
bool Inventory::set_count_for_cell(
        int row,
        int column,
        int count) {
    /**
      **************************************************************************

      **************************************************************************
    */
    bool bool_success = false;
    /**
      **************************************************************************

      **************************************************************************
    */
    if(cell_is_empty(row, column)) {
        return bool_success;
    }
    /**
      **************************************************************************

      **************************************************************************
    */
    if(count == 0) {
        bool_success =
                clear_cell(row, column);

        return bool_success;
    }
    /**
      **************************************************************************

      **************************************************************************
    */
    QSqlDatabase sql_data_base =
            DataBaseManager::get_instance()->get_data_base();
    if(!sql_data_base.isOpen()) {
        qDebug() << "Отсутствует соединение с базой данных: "
                 << sql_data_base.databaseName();
        return bool_success;
    }
    /**
      **************************************************************************

      **************************************************************************
    */
    QSqlQuery sql_query(sql_data_base);

    sql_query.prepare(
                QString("UPDATE inventory "
                        "SET count = :count "
                        "WHERE row = :row AND column = :column"));

    sql_query.bindValue(0, count);
    sql_query.bindValue(1, row);
    sql_query.bindValue(2, column);

    bool_success = sql_query.exec();

    if(!sql_query.isActive())   {
        qDebug() << "Не удалось выполнить запрос к базе данных: "
                 << sql_data_base.databaseName()
                 << QChar('\n')
                 << "Query: "
                 << sql_query.lastQuery()
                 << QChar('\n')
                 << "Сообщение драйвера базы данных: "
                 << sql_query.lastError();
        return bool_success;
    }
    /**
      **************************************************************************

      **************************************************************************
    */
    return bool_success;
}
/**
  ******************************************************************************

  ******************************************************************************
*/
bool Inventory::cell_is_empty(
        int row,
        int column) const {
    /**
      **************************************************************************

      **************************************************************************
    */
    bool bool_success = false;
    /**
      **************************************************************************

      **************************************************************************
    */
    QSqlDatabase sql_data_base =
            DataBaseManager::get_instance()->get_data_base();
    if(!sql_data_base.isOpen()) {
        qDebug() << "Отсутствует соединение с базой данных: "
                 << sql_data_base.databaseName();
        return bool_success;
    }
    /**
      **************************************************************************

      **************************************************************************
    */
    QSqlQuery sql_query(sql_data_base);

    sql_query.prepare(
                QString("SELECT COUNT(*) FROM inventory "
                        "WHERE row = :row AND column = :column"));

    sql_query.bindValue(0, row);
    sql_query.bindValue(1, column);

    sql_query.exec();

    if(!sql_query.isActive())   {
        qDebug() << "Не удалось выполнить запрос к базе данных: "
                 << sql_data_base.databaseName()
                 << QChar('\n')
                 << "Query: "
                 << sql_query.lastQuery()
                 << QChar('\n')
                 << "Сообщение драйвера базы данных: "
                 << sql_query.lastError();
    }
    else if(sql_query.first()) {
        bool_success = sql_query.value(0).toInt() == 0;
    }
    /**
      **************************************************************************

      **************************************************************************
    */
    return bool_success;
}
/**
  ******************************************************************************

  ******************************************************************************
*/
bool Inventory::clear_cell(int row, int column) {
    /**
      **************************************************************************

      **************************************************************************
    */
    bool bool_success = false;
    /**
      **************************************************************************

      **************************************************************************
    */
    QSqlDatabase sql_data_base =
            DataBaseManager::get_instance()->get_data_base();
    if(!sql_data_base.isOpen()) {
        qDebug() << "Отсутствует соединение с базой данных: "
                 << sql_data_base.databaseName();
        return bool_success;
    }
    /**
      **************************************************************************

      **************************************************************************
    */
    QSqlQuery sql_query(sql_data_base);

    sql_query.prepare(
                QString("DELETE FROM inventory "
                        "WHERE row = :row AND column = :column"));

    sql_query.bindValue(0, row);
    sql_query.bindValue(1, column);

    bool_success = sql_query.exec();

    if(!sql_query.isActive())   {
        qDebug() << "Не удалось выполнить запрос к базе данных: "
                 << sql_data_base.databaseName()
                 << QChar('\n')
                 << "Query: "
                 << sql_query.lastQuery()
                 << QChar('\n')
                 << "Сообщение драйвера базы данных: "
                 << sql_query.lastError();
        return bool_success;
    }
    /**
      **************************************************************************

      **************************************************************************
    */
    return bool_success;
}
/**
  ******************************************************************************

  ******************************************************************************
*/
bool Inventory::clear_all_cells() {
    /**
      **************************************************************************

      **************************************************************************
    */
    bool bool_success = false;
    /**
      **************************************************************************

      **************************************************************************
    */
    QSqlDatabase sql_data_base =
            DataBaseManager::get_instance()->get_data_base();
    if(!sql_data_base.isOpen()) {
        qDebug() << "Отсутствует соединение с базой данных: "
                 << sql_data_base.databaseName();
        return bool_success;
    }
    /**
      **************************************************************************

      **************************************************************************
    */
    QSqlQuery sql_query(sql_data_base);

    sql_query.prepare(
                QString("DELETE FROM inventory "));

    bool_success = sql_query.exec();

    if(!sql_query.isActive())   {
        qDebug() << "Не удалось выполнить запрос к базе данных: "
                 << sql_data_base.databaseName()
                 << QChar('\n')
                 << "Query: "
                 << sql_query.lastQuery()
                 << QChar('\n')
                 << "Сообщение драйвера базы данных: "
                 << sql_query.lastError();
        return bool_success;
    }
    /**
      **************************************************************************

      **************************************************************************
    */
    return bool_success;
}
/**
  ******************************************************************************

  ******************************************************************************
*/
int Inventory::count_rows() const {
    return c_int_default_inventory_rows;
}
/**
  ******************************************************************************

  ******************************************************************************
*/
int Inventory::count_columns() const {
    return c_int_default_inventory_columns;
}
