#ifndef INVENTORYMODEL_H
#define INVENTORYMODEL_H
#include <QAbstractTableModel>
#include "inventory.h"

namespace inventory_role
{
const int int_type_role  = Qt::UserRole  + 1;
const int int_count_role = int_type_role + 1;
}

class InventoryModel : public QAbstractTableModel
{
    Q_OBJECT
public:

    explicit InventoryModel(QObject *parent = Q_NULLPTR);

    virtual int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;

    virtual int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;

    virtual QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;

    virtual Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    virtual QMimeData * mimeData(const QModelIndexList & indexes) const Q_DECL_OVERRIDE;

public slots:

    //Сброс модели и очистка БД
    void reset();

protected:
    Inventory inventory;

};

#endif // INVENTORYMODEL_H
