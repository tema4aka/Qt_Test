#ifndef INVENTORY_H
#define INVENTORY_H
#include <QString>

// Размеры инвентаря
const int int_default_inventory_rows      = 3;
const int int_default_inventory_columns   = 3;

//Класс инвентарь

class Inventory
{
public:

    //Метод строит на указанном месте (row, colomn) месте предмет с указанным типом (type)
    //и количеством (count) в ячейке (добавляется новая запись в БД)
    bool emplace_item_to_cell(int row, int column, int type, int count = 1);

    //Метод возвращает тип (ключ в БД) предмета в заданной ячейке
    int get_type_for_cell(int row, int column) const;


    //Метод возвращает путь к изображению предмета, расположенного в
    //заданной ячейке (row, colomn), (расположен в resource.qrc)
    QString get_image_for_cell(int row, int column) const;

    //Getter и Setter для количества предметов в заданной ячейке
    int get_count_for_cell(int row,int column) const;
    bool set_count_for_cell(int row,int column, int count);


    //Проверека на условие отсутсвия предмета в инвентаре в ячейке (row, column)
    bool cell_is_empty(int row, int column) const;


    //Данные методы удаляют из инвентаря (из БД) предмет расположенный
    //в ячейке (row, column) или очищают все таблицу
    bool clear_cell(int row, int column);
    bool clear_all_cells();


    //Методы возвращают количество строк и столбцов в инвентаре
    int count_rows() const;
    int count_columns() const;
};

#endif // INVENTORY_H
