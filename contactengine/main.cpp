#include <QtGui/QApplication>
#include "mainwindow.h"
#include "dbtools.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    DBTools dbt;
    dbt.importCSV("c:\\contacts.csv");

#if defined(Q_WS_S60)
    w.showMaximized();
#else
    w.show();
#endif

    return a.exec();
}
