#include "itemmimedata.h"

ItemMimeData::ItemMimeData() : int_type(), int_count(), bool_is_item(false) {}

ItemMimeData::ItemMimeData(int type, int count) : int_type(type), int_count(count), bool_is_item(true) {}

QStringList	ItemMimeData::formats() const
{
    QStringList string_list_formats = QMimeData::formats();
    string_list_formats.append(QString("application/item"));

    return string_list_formats;
}

bool ItemMimeData::hasFormat(const QString & mimeType) const
{
    if(mimeType == QString("application/item") && bool_is_item)
    {
        return true;
    }

    return QMimeData::hasFormat(mimeType);
}

void ItemMimeData::set_type(int type)
{
    int_type = type;
    bool_is_item = true;
}

void ItemMimeData::set_count(int count)
{
    int_count = count;
}

int ItemMimeData::get_type() const
{
    return int_type;
}

int ItemMimeData::get_count() const
{
    return int_count;
}

