#include <QtCore/QCoreApplication>
#include <QtSql>

#include "database.h"

// This program is simply responsible for creating a SQLite database for the Seafood Selector

void insertFish(QString name, int cat, int calories,
                float fat, float protein, float omega3,
                int cholesterol, int sodium)
{
    QSqlQuery query;

    query.prepare("INSERT INTO fish (name, category, calories, fat, protein,omega3,cholesterol, sodium) "
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

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase db;


    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");


    db.setDatabaseName("C:\\workspace\\qt\\populateDB\\seafood.db");

    // Open databasee
    if(!db.open())
    {
        qDebug() << "DB: failed to open" << endl;
        exit (1);
    }

    qDebug() << "DB: database opened " << endl;

    QSqlQuery query;
    bool rc = true;

   //  rc = query.exec("drop table if exists");

    QString call("create table fish "
                 "(id integer AUTO INCREMENT primary key, "
                 "name varchar(32),"
                 "category int,"
                 "calories int,"
                 "fat float,"
                 "protein float,"
                 "omega3 float,"
                 "cholesterol int,"
                 "sodium int)");

    qDebug() << call << endl;

    rc = query.exec(call);


    insertFish("Crab, Dungeness",EBEST,86,0.96,17.4,0.3,59,295);
    insertFish("Trout, rainbow (farmed)",EBEST,131,5.4,20.8,0.986,59,35);
    insertFish("Cod, Pacific (trawl)",EOK,83,0.63,17.9,0.0,37,71);
    insertFish("Tuna, canned light",EOK,103,1.01,22.0,0.256,47,37);
    insertFish("Orange Roughy",EWORST,69,0.7,14.7,0.02,20,63);
    insertFish("Salmon, farmed or Atlantic",EWORST,142,6.33,19.8,1.73,55,44);

    return a.exec();
}
