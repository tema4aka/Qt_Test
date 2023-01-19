#include <QHeaderView>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QApplication>
#include <QDrag>
#include <QDebug>
#include <QSound>
#include "inventoryview.h"
#include "inventorymodel.h"
#include "inventorydelegate.h"
#include "itemmimedata.h"

InventoryView::InventoryView(QWidget *parent) : QTableView(parent)
{
    //ячейки имеют фиксированный размер, устанавливка значений
    horizontalHeader()->setDefaultSectionSize(test::item_width);
    verticalHeader()->setDefaultSectionSize(test::item_height);

    //Скрытие заголовка таблицы
    horizontalHeader()->hide();
    verticalHeader()->hide();

    //Отключение полосы прокрутки
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //Установка делегата и настройка параметров выделения ячеек
    setItemDelegate(new InventoryDelegate(this));
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setSelectionMode(QAbstractItemView::SingleSelection);

    //Включение поддержки Drag&Drop
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);

    //Фиксация размера виджета
    setFixedSize(3 * test::item_width, 3 * test::item_height);

    //Отключение рамки
    setFrameShape(QFrame::NoFrame);
}

void InventoryView::mousePressEvent(QMouseEvent *event)
{

    QModelIndex model_index = indexAt(event->pos());

    //Обработка клика ПКМ
    if((event->button() == Qt::RightButton))
    {        QAbstractItemModel * m_model = qobject_cast<QAbstractItemModel*>(model());
        if(m_model)
        {
            if(m_model->setData(model_index, model_index.data( inventory_role::int_count_role).toInt() - 1,
                                inventory_role::int_count_role))
            {
                QSound::play(QString("apple.wav"));
            }
        }
    }
    QTableView::mousePressEvent(event);
}

void InventoryView::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasFormat(QString("application/item")))
    {
        event->acceptProposedAction();
    }
}

void InventoryView::dragLeaveEvent(QDragLeaveEvent * event)
{
  Q_UNUSED(event);

  model_index_source_for_drag = QModelIndex();
}

void InventoryView::dragMoveEvent(QDragMoveEvent *event)
{
    QModelIndex model_index =indexAt(event->pos());

    if(model_index_source_for_drag.isValid() && model_index_source_for_drag == model_index)
    {
        event->ignore();
        return;
    }

    int int_current_item_type = model_index.data(inventory_role::int_type_role).toInt();

    if(event->mimeData()->hasFormat(QString("application/item")))
        {
        //Если происходит  перетаскивание целевой ячейки в непустую
        //ячеку с наличием в ней предмета типа отличного от целевого
        //игнорируем дропинг
        if(int_current_item_type != -1 && model_index_source_for_drag.isValid()
           && int_current_item_type != model_index_source_for_drag.data(inventory_role::int_type_role).toInt())
        {
            event->ignore();
            return;
        }
        //Аналогично если источником предмета является внешний виджет
        const ItemMimeData *item_mime_data = static_cast<const ItemMimeData*>(event->mimeData());

        if(item_mime_data && (int_current_item_type != -1)
           && (item_mime_data->get_type() != int_current_item_type))
        {
            event->ignore();
            return;
        }
        event->acceptProposedAction();
    }
}

void InventoryView::dropEvent(QDropEvent *event)
{
    QModelIndex model_index = indexAt(event->pos());
    if(!model_index.isValid())
    {
        return;
    }

    const ItemMimeData * item_mime_data = static_cast<const ItemMimeData*>(event->mimeData());
    if(!item_mime_data)
    {
        return;
    }

    int int_item_key = item_mime_data->get_type();

    QAbstractItemModel *m_model = qobject_cast<QAbstractItemModel*>(model());
    if(!m_model)
    {
        return;
    }
    //Получить тип элемента в ячейке и его количество
    int int_current_item_type = model_index.data(inventory_role::int_type_role).toInt();
    int int_current_item_count = model_index.data(inventory_role::int_count_role).toInt();

      //Двойное условие:
      //Внешнее - если предмет в ячейке и сбрасываемый предмет идентичны
      //Внутреннее - источник MIME данных (внешний объект или текущий виджет)
    if(int_current_item_type == int_item_key )
    {
        if(event->source() != this)
        {
            m_model->setData(model_index, int_current_item_count + 1, inventory_role::int_count_role);
        }
        else
        {
            m_model->setData(model_index, int_current_item_count +
                             model_index_source_for_drag.data(inventory_role::int_count_role).toInt(),
                             inventory_role::int_count_role);

            m_model->setData(model_index_source_for_drag, 0, inventory_role::int_count_role);
        }
    }
    else if(int_current_item_type == -1)
    {
        if(event->source() != this)
        {
            m_model->setData(model_index, int_item_key, inventory_role::int_type_role);
        }
        else
        {
            QList<QVariant> list_item;
            list_item.append(model_index_source_for_drag.data(inventory_role::int_type_role).toInt());

            list_item.append(model_index_source_for_drag.data(inventory_role::int_count_role).toInt());
            QVariant variant;
            variant = list_item;

            if(m_model->setData(model_index, variant, inventory_role::int_type_role))
            {
                m_model->setData(model_index_source_for_drag, 0, inventory_role::int_count_role);
            }
        }
    }
    setCurrentIndex(model_index);
    model_index_source_for_drag = QModelIndex();
}

void InventoryView::startDrag(Qt::DropActions supportedActions)
{
    QModelIndex model_index = currentIndex();
    if(!model_index.isValid())
    {
        return;
    }

    int int_current_item_type = model_index.data(inventory_role::int_type_role).toInt();

    if(int_current_item_type == -1)
    {
        return;
    }

    model_index_source_for_drag = model_index;

    QTableView::startDrag(supportedActions);
}
