#include <QtGui/QApplication>
#include <QWidget>

#include "mainwindow.h"

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
    w.createMenus();
    disableContextMenu();
    w.setWindowTitle("Seafood");
    w.setStyleSheet("* { background-color:rgb(199,147,88); padding: 7px ; color:rgb(255,255,255)}");
#if defined(Q_WS_S60) || defined(Q_WS_MAEMO_5)
    w.showMaximized();
#else
    w.show();
#endif
    return a.exec();
}
