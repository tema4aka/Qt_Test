#ifndef ITEMMIMEDATA_H
#define ITEMMIMEDATA_H

#include <QMimeData>

class ItemMimeData : public QMimeData
{
public:

    ItemMimeData();
    explicit ItemMimeData(int type, int count = 1);

    //Переопределение методов для обработки пользовательских типов MIME данных
    virtual QStringList	formats() const Q_DECL_OVERRIDE;
    virtual bool hasFormat(const QString & mimeType) const Q_DECL_OVERRIDE;

    //Геттеры для типа (ключа в БД) объекта и ее количества
    void set_type(int type);
    void set_count(int count);

    //Сеттеры для типа (ключа в БД) объекта и ее количества
    int get_type() const;
    int get_count() const;

protected:

    //Тип итемки и ее количество
    int int_type;
    int int_count;

    //Флаг указывающий на возможность хранения пользовательского типа MIME данных
    bool bool_is_item;
};

#endif // ITEMMIMEDATA_H
