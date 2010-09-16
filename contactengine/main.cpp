#include <QtGui/QApplication>
#include <QDesktopServices>
#include <QDir>
#include <QDebug>
#include <QLabel>

#ifdef USE_ORANGE_FW
#include <OLApplication.h>
#include <OLPixmapWidget.h>
#include "mainview.h"
#include "contactlist.h"
#else
#include "mainwindow.h"
#include "dbtools.h"
#endif

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

#ifdef USE_ORANGE_FW
int main(int argc, char *argv[])
{
    OLApplication a(argc, argv);

    MainView *mainView = new MainView(NULL);

    disableContextMenu();

    a.setWindowTitle("(OL)Contact App");
    mainView->resize(a.viewSize());
//    QLabel* test = new QLabel("main base view", mainView);
//    Q_UNUSED(test);
    ContactList *cl = new ContactList(mainView);
    Q_UNUSED(cl)
    mainView->connect(&a, SIGNAL(appStarted()), mainView, SLOT(startApp()));

    return a.exec();
}
#else
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;



    DBTools dbt;
    QString dbLocation(":/contacts.csv");

    qDebug() << "dbLocation=" << dbLocation << endl;
    dbt.importCSV(dbLocation);

    disableContextMenu();

    w.setWindowTitle("Contact App");
#if defined(Q_WS_S60)
    w.showMaximized();
#else
    w.show();
#endif
    return a.exec();
}
#endif
