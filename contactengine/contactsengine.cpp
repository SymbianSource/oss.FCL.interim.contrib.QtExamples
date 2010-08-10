#include <QContact>
#include <QContactAddress>
#include <QContactOrganization>
#include <QContactPhoneNumber>

#include "contactsengine.h"

using namespace QtMobility;

ContactsEngine::ContactsEngine(QObject *parent) :
    QAbstractListModel(parent)
{
    this->m_manager = 0;
}
ContactsEngine::~ContactsEngine()
{
    QList<QContactManager*> initialisedManagers = m_initialisedManagers.values();
    while (!initialisedManagers.isEmpty()) {
        QContactManager *deleteMe = initialisedManagers.takeFirst();
        delete deleteMe;
    }
}

void ContactsEngine::setManager(QString aMgrName)
{
    QString managerUri = m_availableManagers.value(aMgrName);

    // first, check to see if they reselected the same backend.
    if (m_manager && m_manager->managerUri() == managerUri)
        return;

    // the change is real.  update.
    if (m_initialisedManagers.contains(managerUri)) {
        m_manager = m_initialisedManagers.value(managerUri);
    } else {
        m_manager = QContactManager::fromUri(managerUri);
        if (m_manager->error()) {
            // todo switch to qDebug()
            // QMessageBox::information(this, tr("Failed!"), QString("Failed to open store!\n(error code %1)").arg(m_manager->error()));
            delete m_manager;
            m_manager = 0;
            return;
        }
        m_initialisedManagers.insert(managerUri, m_manager);
    }

    // compute a new list of contact names
    QStringList displayNames;
    QList<QContact> c = this->m_manager->contacts();

    // signal that the manager has changed.

    // emit managerChanged(m_manager);

    // and... rebuild the list.
    // rebuildList(m_currentFilter);
}

void ContactsEngine::populateAddresses()
{
    QContact *contact;
    QContactOrganization *dept;
    QStringList departmentName;
    QContactPhoneNumber *number;
    QContactAddress *address;

    // this source is open source. Do not put private numbers in here.

    // emergency numbers
    // fire Foster City
    contact = new QContact();

    dept = new QContactOrganization();
    departmentName << "Foster City Fire department";
    dept->setDepartment(departmentName);
    contact->saveDetail(dept);

    number = new QContactPhoneNumber();
    number->setContexts(QContactDetail::ContextWork);
    number->setNumber("+1-650-286-3350?");
    contact->saveDetail(number);
    //fire.setPreferredDetail("DialAction",number); //doesn't compile. Has it been depreciated?

    // create address detail
    address = new QContactAddress();
    address->setCountry("USA");
    address->setRegion("CA");
    address->setLocality("Foster City"); // RFC 2426 - defines the difference locality and region.
    address->setStreet("1040 East Hillsdale Boulevard");
    address->setPostcode("94404");
    contact->saveDetail(address);

    this->m_manager->saveContact(contact);
    // Note that the caller retains ownership of the detail.
    delete dept;
    while (!departmentName.isEmpty())
        departmentName.takeFirst();
    delete number;
    delete address;
    delete contact;

    // police - foster city
    contact = new QContact();

    dept = new QContactOrganization();

    departmentName << "Foster City Police department";
    dept->setDepartment(departmentName);
    contact->saveDetail(dept);

    number = new QContactPhoneNumber();
    number->setContexts(QContactDetail::ContextWork);
    number->setNumber("+1(650)286-3300?");
    contact->saveDetail(number);

    // create address detail
    address = new QContactAddress();
    address->setCountry("USA");
    address->setRegion("CA");
    address->setLocality("Foster City");
    address->setStreet("1030 East Hillsdale Boulevard");
    address->setPostcode("94404");
    contact->saveDetail(address);

    this->m_manager->saveContact(contact);
    delete dept;
    while (!departmentName.isEmpty())
        departmentName.takeFirst();
    delete number;
    delete address;
    delete contact;

    // taxi - Foster City
    contact = new QContact();

    dept = new QContactOrganization();
    departmentName << "Foster City Yellow Cab";
    dept->setDepartment(departmentName);
    contact->saveDetail(dept);

    number = new QContactPhoneNumber();
    number->setContexts(QContactDetail::ContextWork);
    number->setNumber("+1(650)367-9999?");
    contact->saveDetail(number);

    // create address detail
    address = new QContactAddress();
    address->setCountry("USA");
    address->setRegion("CA");
    address->setLocality("Foster City");
    address->setStreet("1055 foster city blvd");
    address->setPostcode("94404");
    contact->saveDetail(address);

    this->m_manager->saveContact(contact);
    delete dept;
    while (!departmentName.isEmpty())
        departmentName.takeFirst();
    delete number;
    delete address;
    delete contact;

    // fire  - Menlo Park
    contact = new QContact();

    dept = new QContactOrganization();
    departmentName << "Menlo Park fire department";
    dept->setDepartment(departmentName);
    contact->saveDetail(dept);

    number = new QContactPhoneNumber();
    number->setContexts(QContactDetail::ContextWork);
    number->setNumber("+1(650)688-8400??");
    contact->saveDetail(number);

    // create address detail
    address = new QContactAddress();
    address->setCountry("USA");
    address->setRegion("CA");
    address->setLocality("Menlo Park");
    address->setStreet("170 Middlefield Road");
    address->setPostcode("94025");
    contact->saveDetail(address);

    this->m_manager->saveContact(contact);
    delete dept;
    while (!departmentName.isEmpty())
        departmentName.takeFirst();
    delete number;
    delete address;
    delete contact;

    //701 Laurel Street, Menlo Park, CA? -
    // police  - Menlo Park
    contact = new QContact();

    dept = new QContactOrganization();
    departmentName << "Menlo Park police department";
    dept->setDepartment(departmentName);
    contact->saveDetail(dept);

    number = new QContactPhoneNumber();
    number->setContexts(QContactDetail::ContextWork);
    number->setNumber("+1(650)858-3328???");
    contact->saveDetail(number);

    // create address detail
    address = new QContactAddress();
    address->setCountry("USA");
    address->setRegion("CA");
    address->setLocality("Menlo Park");
    address->setStreet("701 Laurel Street");
    address->setPostcode("94025");
    contact->saveDetail(address);

    this->m_manager->saveContact(contact);
    delete dept;
    while (!departmentName.isEmpty())
        departmentName.takeFirst();
    delete number;
    delete address;
    delete contact;
}



QStringList ContactsEngine::dataSources()
{
     QStringList availableManagers = QContactManager::availableManagers();
     availableManagers.removeAll("invalid");
     foreach(QString managerName, availableManagers) {

         QMap<QString, QString> params;
         QString managerUri = QContactManager::buildUri(managerName, params);

         // Add some parameters to SIM backend so that we can use
         // all the stores.
         if (managerName == "symbiansim") {
             availableManagers.removeAll("symbiansim");

             availableManagers.append("symbiansim:adn");
             params.insert("store", "ADN");
             managerUri = QContactManager::buildUri(managerName, params);
             m_availableManagers.insert(availableManagers.last(), managerUri);

             availableManagers.append("symbiansim:fdn");
             params.clear();
             params.insert("store", "FDN");
             managerUri = QContactManager::buildUri(managerName, params);
             m_availableManagers.insert(availableManagers.last(), managerUri);

             availableManagers.append("symbiansim:sdn");
             params.clear();
             params.insert("store", "SDN");
             managerUri = QContactManager::buildUri(managerName, params);
             m_availableManagers.insert(availableManagers.last(), managerUri);
         }
         else {
             m_availableManagers.insert(managerName, managerUri);
         }
     }
     return (availableManagers);
}

int ContactsEngine::rowCount(const QModelIndex &parent) const
 {
    QList<QContact> allContacts;
    allContacts = this->m_manager->contacts();
    // return stringList.count();
    return allContacts.count();
 }

QVariant ContactsEngine::data(const QModelIndex &index, int role) const
 {
    QVariant rc;
    QList<QContact> allContacts;

    allContacts = this->m_manager->contacts();

    if (!index.isValid() || index.row() >= allContacts.size()) {
         return rc;
    }
    if (role == Qt::DisplayRole) {
        rc = QVariant(allContacts.at(index.row()).displayLabel());
    }
    return rc;
 }