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

    // index() and parent()  are defined by QAbstractListModel. So we do not
    // need to define the QModelIndex
    // required by list model interface.
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

    QStringList dataSources();

public:
    void populateAddresses();
    void dumpContactMgr(); // use for debugging. Hard to inspect it via Qt Creator.
    void enumerateMgrs();

signals:
    void managerChanged(QStringList containNames);

public slots:
    void setManager(const QString &aMgr);

private:
    QContactManager *m_manager;
    QMap<QString, QString> m_availableManagers;
    QMap<QString, QContactManager*> m_initialisedManagers;

};

#endif // CONTACTSENGINE_H
