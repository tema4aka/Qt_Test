#include <QGridLayout>
#include <QApplication>
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
      inventory_model(new InventoryModel),
      inventory_view(new InventoryView),
      item_label_apple(new ItemLabel),
      item_label_pear(new ItemLabel),
      item_label_plum(new ItemLabel),
      item_label_orange(new ItemLabel),
      push_button(new QPushButton("Главное меню")),
      menu(Q_NULLPTR)
  {
      inventory_view->setModel(inventory_model);

      crate_interface();
      create_connections();

      item_label_apple->set_key(1);
      item_label_pear->set_key(2);
      item_label_plum->set_key(3);
      item_label_orange->set_key(4);

      resize(window_metrics::int_default_width, window_metrics::int_default_height);
  }
MainWindow::~MainWindow()
{
    delete inventory_model;
}

void MainWindow::crate_interface()
{
    QGridLayout *grid_layout = new QGridLayout(this);

    grid_layout->setContentsMargins(window_metrics::int_content_margins, menu_metrics::int_default_height +
                                    window_metrics::int_content_margins, window_metrics::int_content_margins,
                                    window_metrics::int_content_margins);

    grid_layout->addWidget(inventory_view, 0, 0, 2, 1, Qt::AlignCenter);

    QGridLayout * grid_layout_source = new QGridLayout(this);

    grid_layout_source->setMargin(0);
    grid_layout_source->setSpacing(0);

    grid_layout_source->addWidget(item_label_apple, 0, 0, 1, 1, Qt::AlignCenter);

    grid_layout_source->addWidget(item_label_pear, 0, 1, 1, 1, Qt::AlignCenter);

    grid_layout_source->addWidget(item_label_plum, 1, 0, 1, 1, Qt::AlignCenter);

    grid_layout_source->addWidget(item_label_orange, 1, 1, 1, 1, Qt::AlignCenter);

    grid_layout->addLayout(grid_layout_source, 0, 1, 1, 1);

    grid_layout->addWidget(push_button, 1, 1, 1, 1, Qt::AlignCenter);

    widget = new QWidget;
    widget->setLayout(grid_layout);
    setCentralWidget(widget);

    setFixedSize(minimumSizeHint());

    menu = new Menu(this);
    menu->hide();
}

void MainWindow::create_connections()
{
    connect(push_button, SIGNAL(clicked()), SLOT(show_menu()));
    connect(menu, SIGNAL(start()), SLOT(start()));
    connect(menu, SIGNAL(quit()), SLOT(quit()));
}

void MainWindow::show_menu()
{
    widget->setEnabled(false);
    menu->setGeometry(0, 0, this->width(), menu->height());

    menu->move(0, -menu->height());
    menu->show();

    startTimer(10);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    menu->move(0, menu->y() + 1);
    if(menu->geometry().y() >= 0)
    {
        killTimer(event->timerId());
    }
}

void MainWindow::start()
{
    menu->hide();
    inventory_model->reset();
    widget->setEnabled(true);
}

void MainWindow::quit()
{
    QApplication::quit();
}
