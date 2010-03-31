
#include <QDesktopServices>
#include <QMessageBox>
#include <QtGlobal>
#include <QtSql>
#include "Fishes.h"

Fishes::Fishes(QObject *parent) : QObject(parent)
{
    QSqlDatabase db;
    this->dbErrString = "noErr";

    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");

#ifdef Q_OS_SYMBIAN
    QString dbFile = QDesktopServices::storageLocation(QDesktopServices::DataLocation)
                     + '/'  // Qt Universal file separator
                     + "seafood.db";
    dbFile.replace("/","\\");
#else
    // Windows assumed.
    // unfortunately, "C:\Documents and Settings" is corrupted on my home PC. hard coding until I fix it. -jk
    QString dbFile = "C:/workspace/QtExamples/Seafood/populateDB/seafood.db";
#endif
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
        this->dbErrString =  db.lastError().databaseText();

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

/* given the name of a fish, return a list of eco details in html format.
 */
QString Fishes::getEcoDetails(QString name)
{
    QString detailsInHtml;
    QSqlQuery query;
    this->dbErrString = "noErr";

    query.prepare("select details from ecoDetails "
                  "where fid in (select fid from fish where name = :name )");
    query.bindValue(":name",name);

    if (!query.exec())
    {
        QString errCode =  "failed to get eco details " + query.lastError().text();
        qWarning(errCode.toStdString().c_str());
        this->dbErrString = name + " " + query.lastError().text();
    }

    detailsInHtml.append("<html> <title>name</title> <body> <h2>Eco Details</h2> <ul> ");
    while (query.next()){
        detailsInHtml.append( " <li>");
        detailsInHtml.append( query.value(0).toString());
        detailsInHtml.append( "</li> " );
    }
    detailsInHtml.append("</ul> </body> </html> ");
    return  detailsInHtml;
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
