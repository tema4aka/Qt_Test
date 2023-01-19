#ifndef INVENTORYDELEGATE_H
#define INVENTORYDELEGATE_H
#include <QStyledItemDelegate>

//Класс InventoryDelegate делегат для QTableView
class InventoryDelegate : public QStyledItemDelegate
{

    Q_OBJECT
public:

    explicit InventoryDelegate(QObject *parent = Q_NULLPTR);

    //Переопределяемый (Q_DECL_OVERRIDE) virtual метод для отрисовки
    //заливки, ячейки и количества объектов
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const Q_DECL_OVERRIDE;

};

#endif // INVENTORYDELEGATE_H
