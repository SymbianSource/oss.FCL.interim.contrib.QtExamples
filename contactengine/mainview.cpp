#include <QLabel>
#include <QVBoxLayout>

#include <OLApplication.h>
#include <OLButton.h>
#include <OLPixmapWidget.h>
#include "mainview.h"


#include "mainwindow.h"

MainView::MainView(QWidget *parent) :
    QWidget(parent)
{
    // setup toolbar
    OLButton* btn = 0;
    btn = addToolbarButton(":/images/icn_addmenu.png", "call");
    connect(btn, SIGNAL(clicked()), this, SLOT(showAllContacts()));

    btn = addToolbarButton(":/images/icn_addview.png", "SMS");
    connect(btn, SIGNAL(clicked()), this, SLOT(sortByGeo()));
}

 OLButton* MainView::addToolbarButton(const QString& icon, const QString& text)
 {
     OLWidgetList wgtList;
     OLApplication* app = dynamic_cast<OLApplication*>(qApp);
     OLButton* btn = new OLButton();
     QVBoxLayout* btnLayout = new QVBoxLayout(btn);
     btnLayout->setMargin(0);
     btnLayout->setSpacing(5);
     btnLayout->setAlignment(Qt::AlignCenter);
     OLPixmapWidget* btnIcon = new OLPixmapWidget(icon);
     QLabel* btnText = new QLabel(text);
     btnText->setStyleSheet("font-size: 10px;");
     btnLayout->addWidget(btnIcon, 0, Qt::AlignHCenter);
     btnLayout->addWidget(btnText, 0, Qt::AlignHCenter);
     wgtList.append(btnText);
     btn->setLayout(btnLayout);
     app->addToolbarButton(btn, wgtList);

     return btn;
 }

void MainView::startApp()
{
    OLApplication* app = dynamic_cast<OLApplication*>(qApp);
    QSize viewSize = app->viewSize();
    app->setView(this, OLApplication::systemdefault, true);
}

// just should all contacts.
void MainView::showAllContacts()
{
    OLApplication* app = dynamic_cast<OLApplication*>(qApp);
    app->showBanner("(all) NYI", false);
}

// source the list of contacts by proximity to the phone.
void MainView::sortByGeo()
{
    OLApplication* app = dynamic_cast<OLApplication*>(qApp);
    app->showBanner("(geo) NYI", false);
}

// show all contacts at a particular event.
void MainView::showEvents()
{
    OLApplication* app = dynamic_cast<OLApplication*>(qApp);
    app->showBanner("(events) NYI", false);
}

// show call log
void MainView::showLogs()
{
    OLApplication* app = dynamic_cast<OLApplication*>(qApp);
    app->showBanner("(logs) NYI", false);
}
