#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.createMenus();
    w.setWindowTitle("Seafood");
    w.setStyleSheet("* { background-color:rgb(199,147,88); padding: 7px ; color:rgb(255,255,255)}");
#if defined(Q_WS_S60) || defined(Q_WS_MAEMO_5)
    w.showMaximized();
#else
    w.show();
#endif
    return a.exec();
}
