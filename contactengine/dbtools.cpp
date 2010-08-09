#include <QtCore/QCoreApplication>
#include <QtSql>

#include "database.h"
#include "dbtools.h"

bool DBTools::createTable(QString sqlStmt)
{
    QSqlQuery query;
    return query.exec(sqlStmt);
}

int DBTools::getLastInsertRowId()
{
    int rc = -1;
    QSqlQuery query;
    query.exec("select last_insert_rowid()");
    if (!query.exec()) {
        QString errCode =  "last rowid query Failed: " + query.lastError().text();
        qWarning(errCode.toStdString().c_str());

    } else {
        query.next();
        rc = query.value(0).toInt();
    }
    return rc;
}

void DBTools::insertContact( QString name, QString mobile, QString deskphone,
                    int xtn, QString email, QString skype,
                    QString twitter, QString title, int site,
                    int department, int floor)
{
    QSqlQuery query;

    query.prepare("INSERT INTO contacts ( name, mobile, deskphone, xtn, "
                  "email, skype, twitter, title, site, department, floor) "
                  "VALUES (:name,:mobile,:deskphone,:xtn,:email,:skype, "
                  ":twitter, :title, :site, :department, :floor)");

    query.bindValue(":name", name);
    query.bindValue(":mobile", mobile);
    query.bindValue(":deskphone", deskphone);
    query.bindValue(":xtn", xtn);
    query.bindValue(":twitter", twitter);
    query.bindValue(":skype", skype);
    query.bindValue(":email", email);
    query.bindValue(":title", title);
    query.bindValue(":site", site);
    query.bindValue(":department", department);
    query.bindValue(":floor", floor);

    if (!query.exec())
    {
        qDebug() << query.lastError();
        qFatal("Failed to add fish.");
    }
}


bool DBTools::createDB()
{
    QSqlDatabase db;

    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("C:\\workspace\\QtExamples\\contactengine\\contactengine.db");

    // Open databasee
    if(!db.open())
    {
        qDebug() << "DB: failed to open" << endl;
        exit (1);
    }

    qDebug() << "DB: database opened " << endl;

    bool rc = createTable("create table contacts "
                "(cid integer primary key, "
                "name varchar(128),"
                "mobile varchar(128),"
                "deskphone varchar(128),"
                "xtn int,"
                "email varchar(128),"
                "skype varchar(128),"
                "twitter varchar(128),"
                "title varchar(128),"
                "site int,"
                "department int,"
                "floor int");

    return rc;
}

void DBTools::testDB()
{
    createDB();
    insertContact("Tom", "12345", "45678", 22, "tom@symbian.org", "thetom", "tomtom",
                  "Senior Tom", SITE_LONDON, DEPT_TDM, 0);
}

void DBTools::importCSV(QString fileName)
{

}

DBTools::DBTools(QObject *parent)
{
    QObject();
}

DBTools::~DBTools()
{

}
