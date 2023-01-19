#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QApplication>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include "databasemanager.h"
#include "itemlabel.h"
#include "itemmimedata.h"

namespace test
{
const int item_height = 128;
const int item_width  = 128;
}

ItemLabel::ItemLabel(QWidget *parent) : QLabel(parent), int_item_key(), point_drag_position()
{
    //Устанавка рахмера отображения предмета в QTableView
    setFixedSize(QSize(test::item_width, test::item_height));
}

void ItemLabel::mouseMoveEvent(QMouseEvent *event)
{
    if(!(event->buttons() & Qt::LeftButton))
    {
        return;
    }

    if((event->pos() - point_drag_position).manhattanLength() < QApplication::startDragDistance())
    {
        return;
    }

    QDrag *drag = new QDrag(this);
    ItemMimeData *mime_data = new ItemMimeData(int_item_key);
    drag->setPixmap(QPixmap(get_image_for_key()));

    drag->setHotSpot(event->pos());

    drag->setMimeData(mime_data);

    drag->exec(Qt::CopyAction);
}

void ItemLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        point_drag_position = event->pos();
    }
    QLabel::mousePressEvent(event);
}


QString ItemLabel::get_image_for_key() const
{
    QString string_result;

    QSqlDatabase sql_data_base = DataBaseManager::get_instance()->get_data_base();
    if(!sql_data_base.isOpen())
    {
        qDebug() << "Отсутствует соединение с базой данных: "
                 << sql_data_base.databaseName();
        return string_result;
    }

    QSqlQuery sql_query(sql_data_base);

    sql_query.prepare(QString("SELECT image FROM items WHERE key = :key"));

    sql_query.bindValue(0, int_item_key);

    sql_query.exec();

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
    else if(sql_query.first())
    {
        string_result =sql_query.value(0).toString();
    }

    return string_result;
}

void ItemLabel::set_key(int key)
{
    int_item_key = key;

    //Смена изображения для объекта
    setPixmap(QPixmap(get_image_for_key()));
}
