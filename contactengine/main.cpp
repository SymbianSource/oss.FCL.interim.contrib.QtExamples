#include <QtGui/QApplication>
#include <QDesktopServices>
#include <QDir>
#include "mainwindow.h"
#include "dbtools.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    DBTools dbt;
    QString dbLocation;

#ifdef Q_OS_SYMBIAN
        dbLocation = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
        dbLocation.append(QDir::separator());
        dbLocation.append("contacts.csv");

#else
        dbLocation = "C:\\workspace\\QtExamples\\contactengine\\contacts.csv";
#endif
    qDebug() << "dbLocation=" << dbLocation << endl;
    dbt.importCSV(dbLocation);

#if defined(Q_WS_S60)
    w.showMaximized();
#else
    w.show();
#endif

    return a.exec();
}
