#ifndef DETAILSGV_H
#define DETAILSGV_H

#include <QHash>
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QPushButton>

/*
 * This class is a mock up of how the Graphics View architecture might be
 * used to present the details of a contact. It encapsulates all information
 * about Graphics View except the UI Design defines and asks the view itself to the
 * QStackedView.
 *
 * It has no knowledge of the QMainWindow. Widgets in this calls can emit a signal to
 * communicate with the QMainWindow.
 */

class DetailsGV : public QObject
{
    Q_OBJECT
public:
    explicit DetailsGV(QObject *parent, QGraphicsView *gv);

signals:
    void closeMe();
    void backToList();

public slots:

private:
    // We can use normal widgets in a Graphics View. This one creates some push buttons.
    void createWidgets();
    // If you use normal widgets, you'll need to use a proxy to communite between them and the graphics view.
    void createProxyWidgets();
    void createLayout();
    // customize the view
    void customizeView();
    void createConnections();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPushButton *callMe;
    QPushButton *textMe;
    QPushButton *back;
    QPushButton *exitApp;

    QHash<QString, QGraphicsProxyWidget*> proxyForName;
};

#endif // DETAILSGV_H
