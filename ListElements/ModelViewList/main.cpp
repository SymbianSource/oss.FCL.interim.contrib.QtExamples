

#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_S60DontConstructApplicationPanes);
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Zodiac");
#if defined(Q_WS_S60)
    // w.showMaximized();
    w.showFullScreen();
#else
    w.show();
#endif
    a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );

    return a.exec();


}
