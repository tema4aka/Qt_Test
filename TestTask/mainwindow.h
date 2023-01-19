#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "inventorymodel.h"
#include "inventoryview.h"
#include "itemlabel.h"
#include "menu.h"

namespace window_metrics
{
const int int_default_height = 1024;
const int int_default_width  = 1280;
const int int_content_margins = 3;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = Q_NULLPTR);

    virtual ~MainWindow();
protected:
    //Метод для создания QGridLayouts и помещения виджетов в layouts
    void create_interface();

    //Метод для создания связей между slots и signals (connect:)
    void create_connections();

    //Метод обновления окна
    virtual void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

public slots:

    void show_menu();
private slots:

    void start();
    void quit();
private:

    InventoryModel *inventory_model;
    InventoryView *inventory_view;
    ItemLabel *item_label_apple;

    QPushButton *push_button;

    Menu *menu;

    QWidget *widget;
};
#endif // MAINWINDOW_H
