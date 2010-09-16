#include <OLApplication.h>
#include <QMessageBox>
#include "contactlist.h"

ContactList::ContactList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    this->ce = new ContactsEngine(this);

    connect(this->ce, SIGNAL(errorOccurred(QString)),
            this,SLOT(errorOccurred(QString)));

    this->ce->createManager();

    connect(ui->comboBox, SIGNAL( activated ( const QString &  )),
            this->ce, SLOT(setManager(const QString &) ));


    ui->comboBox->addItems(this->ce->dataSources());
    ui->listView->setModel(this->ce);

}


void ContactList::errorOccurred(QString err)
{
    QMessageBox::information(this, "foo", err);
}

// just should all contacts.
void ContactList::showAllContacts()
{
    OLApplication* app = dynamic_cast<OLApplication*>(qApp);
    app->showBanner("(all) NYI", false);
}

// source the list of contacts by proximity to the phone.
void ContactList::sortByGeo()
{
    OLApplication* app = dynamic_cast<OLApplication*>(qApp);
    app->showBanner("(geo) NYI", false);
}

// show all contacts at a particular event.
void ContactList::showEvents()
{
    OLApplication* app = dynamic_cast<OLApplication*>(qApp);
    app->showBanner("(events) NYI", false);
}

// show call log
void ContactList::showLogs()
{
    OLApplication* app = dynamic_cast<OLApplication*>(qApp);
    app->showBanner("(logs) NYI", false);
}
