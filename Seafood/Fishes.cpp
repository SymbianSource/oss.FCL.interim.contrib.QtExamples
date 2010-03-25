
#include <QDesktopServices>
#include <QMessageBox>
#include <QtGlobal>
#include <QtSql>
#include "Fishes.h"

Fishes::Fishes(QObject *parent) : QObject(parent)
{
    QSqlDatabase db;

    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");

    QString dbFile = QDesktopServices::storageLocation(QDesktopServices::DataLocation)
                     + '/'  // Qt Universal file separator
                     + "seafood.db";
    QFile f(dbFile);
    std::string errString(dbFile.toStdString());
    if (!f.exists()) {
        qWarning("db not found ");
    } else {
        qWarning("found db ");
    }
    qWarning(dbFile.toStdString().c_str());
    db.setDatabaseName(dbFile);

    // Open databasee
    if(!db.open())
    {
        std::string errCode =  db.lastError().databaseText().toStdString();

        qWarning("DB: failed to open.");

        this->bestFish << "Abalone (farmed)" << "Anchovy, European" << "Barramundi U.S."
            << "Capelin, smelt roe (Iceland)" << "Catfish (U.S.)" << "Clam, softshell"
            << "Clams (farmed)" << "Cod, AK (longline)" << "Crab, Dungeness"
            << "Crab, stone" << "Mussels" << "Oysters (farmed)"
            << "Sablefish/ Black Cod (Alaska, Canada)" << "Salmon, wild (Alaska)"
            << "Sardines, Pacific (U.S.)" << "Shrimp, pink (Oregon)"
            << "Trout, rainbow (farmed)" << "Tuna, albacore (U.S., Canada)";
        this->okFish << "Clams (wild)" << "Cod, Pacific (trawl)" << "Crab, Snow"
            << "Flounder/sole (Pacific)" << "Lobster, American/Maine" << "Scallops, sea (U.S., Canada)"
            << "Shrimp (U.S. wild)" << "Squid" << "Tilapia (Latin America)"
            << "Tuna, canned light";
        this->worstFish << "Chilean sea bass" << "Grouper" << "Orange roughy"
            << "Rockfish (trawl)" << "Salmon, farmed or Atlantic" << "Shark"
            << "Swordfish (imported)" << "Tilefish (Gulf of Mexico/South Atlantic)"
            << "Tuna, bigeye/yellowfin" << "Tuna, bluefin";
    } else {
        this->populate(EPresentBest);
        this->populate(EPresentOK);
        this->populate(EPresentWorst);
    }
}

void Fishes::populate(TCATEGORIES cat)
{
    QSqlQuery query;

    query.prepare("SELECT name FROM fish where category = :category ");
    query.bindValue(":category",cat);

    if (!query.exec())
    {
        QString errCode =  "failed to populate " + query.lastError().text();
        qWarning(errCode.toStdString().c_str());
        //qFatal("Failed to add fish.");
    }

    while (query.next()){
        switch (cat)
        {
        case  EPresentBest:
            this->bestFish << query.value(0).toString();
            break;
        case EPresentWorst:
            this->worstFish << query.value(0).toString();
            break;
        case EPresentOK:
            this->okFish << query.value(0).toString();
            break;
        default:
            qWarning("this can't happen.");
            break;
        }
    }

}


const QStringList Fishes::GetBest()
{

    return bestFish;
}

const QStringList Fishes::GetOK()
{
    return okFish;
}

const QStringList Fishes::GetWorst()
{
    return worstFish;
}
