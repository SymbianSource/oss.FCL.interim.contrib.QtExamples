#include "detailsgv.h"

#include <QColor>
#include <QGraphicsTextItem>
#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <QGraphicsAnchorLayout>
#include <QGraphicsPixmapItem>
#include <QGraphicsSvgItem>
#include <QPixmap>
#include <QTransform>

DetailsGV::DetailsGV(QObject *parent,QGraphicsView *gv) :
    QObject(parent), view(gv)
{
    scene = new QGraphicsScene(this);
    gv->setScene(scene);
    this->createWidgets();
    this->createProxyWidgets();
    this->createLayout();
    this->createConnections();
    this->customizeView();
}


void DetailsGV::createWidgets()
{
    QString styleSheet("background-color:red");
    callMe = new QPushButton(tr("call us"));
    callMe->setStyleSheet(styleSheet);
    textMe = new QPushButton(tr("text us"));
    textMe->setStyleSheet(styleSheet);
    back = new QPushButton (tr("back"));
    back->setStyleSheet(styleSheet);
    exitApp = new QPushButton(tr("exit"));
    exitApp->setStyleSheet(styleSheet);
}

void DetailsGV::createProxyWidgets()
{
    proxyForName["callMe"] = scene->addWidget(callMe);
    proxyForName["textMe"] = scene->addWidget(textMe);
    proxyForName["back"] = scene->addWidget(back);
    proxyForName["exitApp"] = scene->addWidget(exitApp);
}

void DetailsGV::createLayout()
{
    // row of buttons
    QGraphicsLinearLayout *leftLayout = new QGraphicsLinearLayout(Qt::Vertical);
    leftLayout->addItem(proxyForName["callMe"]);
    leftLayout->addItem(proxyForName["textMe"]);
    leftLayout->addItem(proxyForName["back"]);
    leftLayout->addItem(proxyForName["exitApp"]);

     // looks like there is a bug with respect to displaying jpeg's in a scene on Symbian^1.
     // I've asked about it on the mailing list QtS60-feedback@trolltech.com.
     //QGraphicsPixmapItem *profile = new QGraphicsPixmapItem( QPixmap(":/images/MadProf_thumb.jpg"));
     // strange returns width of screen not button ?
     // int w = this->callMe->width();
     // profile->setX(100);

     // svg from open clipart (http://www.openclipart.org/detail/959)
     QGraphicsSvgItem *profile = new QGraphicsSvgItem(":/images/johnny_automatic_marching_band_1.svg");
     profile->scale(0.5,0.5);
     profile->setX(32);

     QGraphicsAnchorLayout *aLayout = new QGraphicsAnchorLayout;
     aLayout->addAnchor(leftLayout,Qt::AnchorLeft,aLayout,Qt::AnchorLeft);
     aLayout->addAnchor(leftLayout,Qt::AnchorTop,aLayout,Qt::AnchorTop);

    // address
     QGraphicsTextItem *address = new QGraphicsTextItem();
     address->setDefaultTextColor(QColor(Qt::darkRed));
     address->setHtml("<b>Symbian Foundation West</b><br/>Foster City<br/>California");
     address->setPos(25, 225);

     QGraphicsWidget *widget = new QGraphicsWidget;
     widget->setLayout(aLayout);
     scene->addItem(profile);
     scene->addItem(address);
     scene->addItem(widget);
}


void DetailsGV::customizeView()
{
    view->setBackgroundBrush(QColor("bisque"));
    view->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
}

void DetailsGV::createConnections()
{
    // if someone clicks on the exit button, propogate it to the QMainWindow.
    connect(this->exitApp, SIGNAL(clicked()),this,SIGNAL(closeMe()));
}
