#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QPushButton>

namespace menu_metrics {
const int int_default_height = 32;
const int int_content_margins = 2;
}

class Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Menu(QWidget *parent = Q_NULLPTR);
    void create_interface();
    void create_connections();
signals:

    void start();
    void quit();
protected:

    QPushButton *push_button_start;
    QPushButton *push_button_quit;
};

#endif // MENU_H
