#ifndef ITEMLABEL_H
#define ITEMLABEL_H

#include <QLabel>

class ItemLabel : public QLabel
{
    Q_OBJECT
public:

    explicit ItemLabel(QWidget *parent = Q_NULLPTR);

    virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    void set_key(int key);
protected:
    QString get_image_for_key() const;

    int int_item_key;

    QPoint point_drag_position;
};

#endif // ITEMLABEL_H
