#include <QContact>
#include <QContactAddress>
#include <QContactName>
#include <QContactOrganization>
#include <QContactPhoneNumber>


#include "contactsengine.h"

#include <QDebug>

using namespace QtMobility;

ContactsEngine::ContactsEngine(QObject *parent) :
    QAbstractListModel(parent)
{
    this->m_manager = 0;
}

ContactsEngine::~ContactsEngine()
{

}

//void ContactsEngine::createManager()
//{
//    // this->m_manager = new QContactManager("symbian");
//    // let's try the default.
//    this->m_manager = new QContactManager();
//}

void ContactsEngine::createManager()
{
    // adapted from http://wiki.forum.nokia.com/index.php/Finding_contact_manager_in_Qt

    // Get list of different contact back-ends
    QStringList availableManagers = QContactManager::availableManagers();

    QList<QContactLocalId> contactIds;
    // Try to find contacts from some back-end
    while (!availableManagers.isEmpty()) {
        // Get some manager
        m_manager = new QContactManager(availableManagers.first());
        availableManagers.removeFirst();

        // Contacts exists?
        contactIds = m_manager->contactIds();
        if (!contactIds.isEmpty()) {
            // Contact found
            availableManagers.clear();
            break;
        }
        else {
            // Not found, try the next manager
            delete m_manager;
            m_manager = 0;
        }
    }

    // Use default if no contact found from any back-end
    if (!m_manager) {
        m_manager = new QContactManager();
    }

    // Show message to the user
    QString msg = QString("Manager %1 created, that has %2 contacts")
                  .arg(m_manager->managerName()).arg(contactIds.count());

   // emit errorOccurred(msg);
}


void ContactsEngine::setManager(const QString & aMgrName)
{
   // noop
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
    number->setNumber("+1-650-286-3350");
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
    number->setNumber("+1(650)286-3300");
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
    number->setNumber("+1(650)367-9999");
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
    number->setNumber("+1(650)688-8400");
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
    number->setNumber("+1(650)858-3328");
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
    int rc = 0;
    if (this->m_manager)
    {
        allContacts = this->m_manager->contacts();
        // return stringList.count();
        if (!allContacts.isEmpty())
            rc = allContacts.count();
    }
    return rc;
 }

void ContactsEngine::enumerateMgrs()
{
    QStringList mgrs = QContactManager::availableManagers();
    qDebug() << "Enumerate available Contact Managers:" << endl;
    foreach(QString m, mgrs)
    {
        qDebug() << "\tmgr: " << m << endl;
        this->dumpContactMgr();
    }
    qDebug() << endl;
}

// dump the current contact manager.
void  ContactsEngine::dumpContactMgr()
{
    qDebug() << "Dump Contact Manager:" << endl;
    if (this->m_manager) {
        qDebug() << "\tname: " << this->m_manager->managerName() << endl;
        qDebug() << "\tURI: "  << this->m_manager->managerUri() << endl;
        qDebug() << "\tVersion: "  << this->m_manager->managerVersion() << endl;
        qDebug() << "\tCount:" << this->m_manager->contacts().count() << endl;
    } else {
        qDebug() << "\t Contact Manager set to zero." << endl;
    }
    qDebug() << endl;
}

QVariant ContactsEngine::data(const QModelIndex &index, int role) const
 {
    QVariant rc;
    QList<QContact> allContacts;
    QContact c;

    allContacts = this->m_manager->contacts();

    if (!index.isValid() || index.row() >= allContacts.size()) {
         return rc;
    }
    if (role == Qt::DisplayRole) {
        //rc = QVariant(allContacts.at(index.row()).displayLabel());
        c = allContacts.at(index.row());
        // organizations do not have first and last names.  So the displayLabel() is empty.
        QContactDetail cd = c.detail(QContactName::DefinitionName);
        if (cd.isEmpty()) {
            rc = QVariant (c.detail(QContactOrganization::DefinitionName).value(QContactOrganization::FieldDepartment) );
        } else {
            rc = QVariant ( c.displayLabel());
        }
    }
    return rc;
 }
