#include <QMimeData>
#include <QDebug>
#include "itemmimedata.h"
#include "inventorymodel.h"

InventoryModel::InventoryModel(QObject *parent) : QAbstractTableModel(parent), inventory() {}

int InventoryModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    int int_count_rows = inventory.count_rows();
    return int_count_rows;
}

int InventoryModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    int int_count_columns = inventory.count_columns();
    return int_count_columns;
}

QVariant InventoryModel::data(const QModelIndex &index, int role) const
{
    QVariant variant_result;
    if(!index.isValid())
    {
        return variant_result;
    }

    switch (role)
    {
    case Qt::DecorationRole:
    {
        variant_result = inventory.get_image_for_cell(index.row(), index.column());
    }
        break;
    case inventory_role::int_type_role:
    {
        variant_result =inventory.get_type_for_cell(index.row(), index.column());
    }
        break;
    case inventory_role::int_count_role:
    {variant_result = inventory.get_count_for_cell(index.row(), index.column());
    }
        break;
    }
    return variant_result;
}

bool InventoryModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool bool_success = false;
    if(!index.isValid())
    {
        return bool_success;
    }
    switch (role)
    {
    case inventory_role::int_type_role:
    {
        if(value.canConvert(QMetaType::Int))
        {
            bool_success = inventory.emplace_item_to_cell(index.row(), index.column(), value.toInt());

            if(bool_success)
            {
                emit dataChanged(index, index, QVector<int>(1, inventory_role::int_type_role));
            }
        }

        if(value.canConvert<QList<QVariant>>())
        {
            Q_ASSERT(value.toList().size() >= 2);

            bool_success = inventory.emplace_item_to_cell(index.row(), index.column(), value.toList().at(0).toInt(),
                                                          value.toList().at(1).toInt());
            if(bool_success)
            {
                emit dataChanged(index, index, QVector<int>(1, inventory_role::int_type_role));
            }
        }
    }
        break;
    case inventory_role::int_count_role:
    {
        if(value.canConvert(QMetaType::Int))
        {
            bool_success = inventory.set_count_for_cell(index.row(), index.column(), value.toInt());

            if(bool_success)
            {
                emit dataChanged(index, index, QVector<int>(1, inventory_role::int_count_role));
            }
        }
    }
        break;
    }
    return bool_success;
}

Qt::ItemFlags InventoryModel::flags(const QModelIndex &index) const
{
    if(index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | QAbstractTableModel::flags(index);

    return QAbstractTableModel::flags(index);
}

QMimeData *InventoryModel::mimeData(const QModelIndexList & indexes) const
{
    ItemMimeData *mime_data = new ItemMimeData;

    //Так как в виде установлено ограничение на одиночное выделение ячеек
    //ограничиваемся только одним модельным индексом
    if(indexes.size())
    {
        mime_data->set_type(indexes.at(0).data(inventory_role::int_type_role).toInt());
        mime_data->set_count(indexes.at(0).data(inventory_role::int_count_role).toInt());
    }
    return mime_data;
}

void InventoryModel::reset()
{
    beginResetModel();
    inventory.clear_all_cells();
    endResetModel();
}

