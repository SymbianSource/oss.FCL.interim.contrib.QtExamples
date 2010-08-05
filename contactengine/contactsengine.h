#ifndef CONTACTSENGINE_H
#define CONTACTSENGINE_H

#include <QAbstractListModel>

#include <QContactManager>

#include "contactsengine.h"

using namespace QtMobility;

class ContactsEngine : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ContactsEngine(QObject *parent = 0);
    ~ContactsEngine();

    // required by list model interface.
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

    QStringList dataSources();
    void setManager(QString aMgr);

public:
    void populateAddresses();

signals:
    void managerChanged(QStringList containNames);

public slots:

private:
    QContactManager *m_manager;
    QMap<QString, QString> m_availableManagers;
    QMap<QString, QContactManager*> m_initialisedManagers;
};

#endif // CONTACTSENGINE_H
