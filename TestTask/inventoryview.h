#ifndef INVENTORYVIEW_H
#define INVENTORYVIEW_H
#include <QTableView>

namespace test
{
const int item_height = 128;
const int item_width  = 128;
}

class InventoryView : public QTableView
{
public:
    explicit InventoryView(QWidget *parent = Q_NULLPTR);

protected:
    //Переопределение метода для обработки нажатия ПКМ клавиши мыши
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    //Событие, которе отправляется виджету, когда в него поступает Drop&Drag
    virtual void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;

    //Метод события отпускания объекта
    virtual void dragLeaveEvent(QDragLeaveEvent * event) Q_DECL_OVERRIDE;

    //Метод события выполнения перетаскивания
    virtual void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;

    //Метод события завершения перетаскивания
    virtual void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;

    //Метод начала перетаскивания
    virtual void startDrag(Qt::DropActions supportedActions) Q_DECL_OVERRIDE;

    QModelIndex model_index_source_for_drag;
};

#endif // INVENTORYVIEW_H
