#include <QtCore/QCoreApplication>
#include <QtSql>

#include "database.h"

// This program is simply responsible for creating a SQLite database for the Seafood Selector

void createTable(QString sqlStmt)
{
    QSqlQuery query;
    bool rc = true;
    rc = query.exec(sqlStmt);
}

int getLastInsertRowId()
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

void insertFish( QString name, int cat, int calories,
                float fat, float protein, float omega3,
                int cholesterol, int sodium)
{
    QSqlQuery query;

    query.prepare("INSERT INTO fish ( name, category, calories, fat, protein,omega3,cholesterol, sodium) "
                  "VALUES (:name,:category,:calories,:fat,:protein,:omega3,:cholesterol, :sodium) ");
    query.bindValue(":name", name);
    query.bindValue(":category",cat);
    query.bindValue(":calories",calories);
    query.bindValue(":fat",fat);
    query.bindValue(":protein",protein);
    query.bindValue(":omega3",omega3);
    query.bindValue(":cholesterol",cholesterol);
    query.bindValue(":sodium", sodium);
    if (!query.exec())
    {
        qDebug() << query.lastError();
        qFatal("Failed to add fish.");
    }
}

void insertEco(int lastID, QString details)
{

    QSqlQuery query;

    query.prepare("INSERT INTO ecoDetails (lastID, details) VALUES (:lastID,:details) ");
    query.bindValue(":lastID", lastID);
    query.bindValue(":details",details);
    if (!query.exec())
    {
        qDebug() << query.lastError();
        qFatal("Failed to add eco detail.");
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase db;

    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("C:\\workspace\\QtExamples\\Seafood\\populateDB\\seafood.db");

    // Open databasee
    if(!db.open())
    {
        qDebug() << "DB: failed to open" << endl;
        exit (1);
    }

    qDebug() << "DB: database opened " << endl;

    createTable("create table fish "
                "(lastID integer primary key, "
                "name varchar(32),"
                "category int,"
                "calories int,"
                "fat float,"
                "protein float,"
                "omega3 float,"
                "cholesterol int,"
                "sodium int)");

    createTable ("create table ecoDetails (eid integer primary key, "
                 "lastID integer, "
                 "details varchar(128))");

    int lastID = -1;
    insertFish("Crab, Dungeness",EBEST,86,0.96,17.4,0.3,59,295);
    lastID = getLastInsertRowId();
    insertEco(lastID,"Only adult males are caught in this fishery, which uses pots and traps made of biodegradable webs to avoid \'ghost fishing\' from lost gear.");
    insertEco(lastID, "Pots and traps are also equipped with built-in exits that allow escape of undersize crabs.");
    insertEco(lastID, "This gear has negligible bycatch and causes little habitat damage.");

    insertFish("Trout, rainbow (farmed)",EBEST,131,5.4,20.8,0.986,59,35);
    lastID = getLastInsertRowId();
    insertEco(lastID, "Although trout consume considerable amounts of wild fish in their feed, recent improvements have made them less reliant on this finite natural resource.");
    insertEco(lastID, "Industry practices and stringent government regulations also prevent pollution and fish escapes.");

    insertFish("Cod, Pacific (trawl)",EOK,83,0.63,17.9,0.0,37,71);
    lastID = getLastInsertRowId();
    insertEco(lastID, "U.S. Pacific cod populations are healthy, and cod caught by bottom longline, traps or hook-and-line do the least environmental harm.");
    insertEco(lastID, "U.S. Pacific cod are also caught by bottom trawl, which can damage seafloor habitats.");

    insertFish("Tuna, canned light",EOK,103,1.01,22.0,0.256,47,37);
    lastID = getLastInsertRowId();
    insertEco(lastID, "Canned light tuna consists primarily of skipjack. These small tunas are resilient to fishing pressure because of their short life spans and rapid growth and reproduction rates.");
    insertEco(lastID, "Most skipjack are caught by pole-and-line (a method of fishing that does relatively little ecological harm) or purse seine fleets (which can result in considerable bycatch).");
    insertEco(lastID, "This highly migratory species is managed by international organizations.");

    insertFish( "Orange Roughy",EWORST,69,0.7,14.7,0.02,20,63);
    lastID = getLastInsertRowId();
    insertEco(lastID, "Orange roughy mature at a very slow rate and live extremely long lives. Intensive exploitation in past decades has greatly decreased populations.");
    insertEco(lastID, "Management in New Zealand and Australia is good, but unregulated landings by other countries continue.");

    insertFish("Salmon, farmed or Atlantic",EWORST,142,6.33,19.8,1.73,55,44);
    lastID = getLastInsertRowId();
    insertEco(lastID, "Atlantic salmon are usually farmed in large-scale, densely stocked netpens that pollute surrounding waters with waste and chemicals.");
    insertEco(lastID, "Fish can escape and compete for resources, breed with or spread parasites to wild fish.");

    return 0;
}
