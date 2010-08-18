#include <QtGui/QApplication>
#include <QDesktopServices>
#include <QDir>
#include "mainwindow.h"
#include "dbtools.h"
#include <QDebug>

// Tech Tip: By default, Actions is added to the Options menu. The
// idea is to support context menus on non-touch mobiles.
void disableContextMenu()
{
    QWidgetList widgets = QApplication::allWidgets();
    QWidget* wid=0;
    foreach(wid,widgets)
    {
        wid->setContextMenuPolicy(Qt::NoContextMenu);
    }
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    DBTools dbt;
    QString dbLocation(":/contacts.csv");

    qDebug() << "dbLocation=" << dbLocation << endl;
    dbt.importCSV(dbLocation);

    disableContextMenu();

    w.setWindowTitle("Qt Study App");
#if defined(Q_WS_S60)
    w.showMaximized();
#else
    w.show();
#endif

    return a.exec();
}
