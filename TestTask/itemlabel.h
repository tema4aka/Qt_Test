#ifndef ITEMLABEL_H
#define ITEMLABEL_H

#include <QLabel>

class ItemLabel : public QLabel
{
    Q_OBJECT
public:

    explicit ItemLabel(QWidget *parent = Q_NULLPTR);

    //Переопределение метода обработки движения мыши
    virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    //Переопределение метода для обработки нажатия ЛКМ клавиши мыши
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    //Метод меняет тип объекта (key)
    void set_key(int key);
protected:
    //Метод возвращает путь к изображению предмета для заданного типа объекта (key в БД)
    QString get_image_for_key() const;

    int int_item_key;

    QPoint point_drag_position;
};

#endif // ITEMLABEL_H
