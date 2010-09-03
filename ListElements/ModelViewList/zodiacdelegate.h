#ifndef ZODIACDELEGATE_H
#define ZODIACDELEGATE_H

#include <QModelIndex>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>


class ZodiacDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ZodiacDelegate(QObject *parent=0):QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

};

#endif // ZODIACDELEGATE_H
