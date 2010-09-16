#ifndef CONTACTLIST_H
#define CONTACTLIST_H

#include <QWidget>

#include "contactsengine.h"
#include "ui_ContactList.h"

class ContactList : public QWidget
{
    Q_OBJECT
public:
    explicit ContactList(QWidget *parent = 0);

signals:

public slots:
    // just should all contacts.
    void showAllContacts();
    // source the list of contacts by proximity to the phone.
    void sortByGeo();
    // show all contacts at a particular event.
    void showEvents();
    // show call log
    void showLogs();

    void errorOccurred(QString);

private:
    Ui::Form *ui;
    ContactsEngine *ce;
};

#endif // CONTACTLIST_H
