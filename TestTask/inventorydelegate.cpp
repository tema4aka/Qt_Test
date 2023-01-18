#include <QApplication>
#include <QPainter>
#include "inventorydelegate.h"
#include "inventorymodel.h"

InventoryDelegate::InventoryDelegate(QObject *parent): QStyledItemDelegate(parent) {}

void InventoryDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{

     //отрисовка заливки выделенного элемента
    if(option.state & QStyle::State_Selected)
    {
        painter->fillRect(option.rect, QBrush(Qt::lightGray));
    }

      //Отрисовка ячейки если количество объектов в отлично от нуля
      //Для отрисовки неактивной иконки объекта проверяется состояние родителя делегата

    if(index.data(inventory_role::int_count_role).canConvert(QMetaType::Int) &&
            index.data(Qt::DecorationRole).canConvert(QMetaType::QString))
    {
        int int_item_count = index.data(inventory_role::int_count_role).toInt();

        if(int_item_count > 0)
        {
            //Отрисовка иконки
            QWidget * widget_parent = static_cast<QWidget *>(parent());
            if(widget_parent && widget_parent->isEnabled())
            {
                painter->drawPixmap(option.rect, QPixmap(index.data(Qt::DecorationRole).toString()));
            }
            else
            {
                painter->drawPixmap(option.rect, QIcon(index.data(Qt::DecorationRole).toString())
                                    .pixmap(option.rect.size(),QIcon::Disabled, QIcon::Off));
            }
            //Отрисовка количества объектов
            QString string_result = QString("x%1").arg(QString::number(int_item_count));

            painter->drawText(option.rect, Qt::AlignBottom | Qt::AlignRight, string_result);
        }
    }
}
