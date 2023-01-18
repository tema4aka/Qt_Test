#ifndef INVENTORYDELEGATE_H
#define INVENTORYDELEGATE_H
#include <QStyledItemDelegate>

class InventoryDelegate : public QStyledItemDelegate
{

    Q_OBJECT

public:

    explicit InventoryDelegate(QObject *parent = Q_NULLPTR);

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // INVENTORYDELEGATE_H
