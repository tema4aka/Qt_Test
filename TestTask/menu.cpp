#include <QGridLayout>
#include "menu.h"

Menu::Menu(QWidget *parent) : QWidget(parent), push_button_start(new QPushButton(QString("Начать"))),
                              push_button_quit(new QPushButton(QString("Выход")))
{
    setFixedHeight(menu_metrics::int_default_height);
    create_interface();
    create_connections();
}

void Menu::create_interface()
{
    QGridLayout *grid_layout = new QGridLayout(this);

    grid_layout->setMargin(menu_metrics::int_content_margins);
    grid_layout->addWidget(push_button_start, 0, 0, 1, 1, Qt::AlignCenter);
    grid_layout->addWidget(push_button_quit, 0, 1, 1, 1, Qt::AlignCenter);

    setLayout(grid_layout);
}

void Menu::create_connections()
{
    connect(push_button_start, SIGNAL(clicked()), SIGNAL(start()));
    connect(push_button_quit,  SIGNAL(clicked()), SIGNAL(quit()));
}
