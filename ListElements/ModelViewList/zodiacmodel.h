#ifndef ZODIACMODEL_H
#define ZODIACMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "zodiacsign.h"

class ZodiacModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ZodiacModel(QObject *parent = 0);

    int rowCount (const QModelIndex &index = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role)const;
signals:

public slots:

private:
    QList <ZodiacSign*> signs;
};

#endif // ZODIACMODEL_H
