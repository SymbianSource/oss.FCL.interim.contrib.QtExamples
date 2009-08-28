#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QCloseEvent>
#include <QString>

#include <QtGui/QTreeView>
#include <QtGui/QWidget>

#include <QtXml/QDomDocument>

#include "DomModel.h"

class Document : public QTreeView
{
    Q_OBJECT

public:
    Document(QWidget *parent,QString);

private:
    DomModel *model;
};

#endif // DOCUMENT_H
