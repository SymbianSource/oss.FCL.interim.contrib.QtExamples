#include <QFile>
#include <QIcon>
#include <QListWidget>
#include <QMessageBox>
#include <QStackedWidget>
#include <QTableWidget>
#include <QDesktopServices>
#include <QWebView>

#include "Fishes.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setContextMenuPolicy(Qt::NoContextMenu);
    this->fishDb = new Fishes(this);

    this->stackedWidget = new QStackedWidget;

    // lists of fish
    this->tabWidget = new QTabWidget;

    this->bestList = new QListWidget;
    this->bestList->addItems(this->fishDb->getBest());
    this->tabWidget->addTab(this->bestList, "best");

    this->okList = new QListWidget;
    this->okList->addItems(this->fishDb->getOK());
    this->tabWidget->addTab(this->okList, "ok");

    this->worstList = new QListWidget;
    this->worstList->addItems(this->fishDb->getWorst());
    this->tabWidget->addTab(this->worstList, "worst");

    this->index = EBestList;

    connect(this->tabWidget, SIGNAL(currentChanged(int)),
            this, SLOT(setCurrentList(int)));

    this->stackedWidget->addWidget(tabWidget); // associated with EListPage

    // Eco details

    this->ecoDetails = new QWebView;
    this->ecoDetails->setHtml("<html><title>Eco Details</title><ul><li>not yet implemented</li></ul></html>");

    this->stackedWidget->addWidget(this->ecoDetails); // associated with EEcoPage

    // Nutrition page
    // this->model = new QSqlQueryModel;
    // this->model->
    this->stackedWidget->addWidget(ui->centralWidget); // associated with ENutritionPage


    setCentralWidget(stackedWidget);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenus()
    {

        ecoAction = new QAction(tr("&eco details"),this);
        menuBar()->addAction(ecoAction);
        connect(ecoAction, SIGNAL(triggered()),this, SLOT(displayEcoDetails()));

        nuAction = new QAction(tr("&Nutrition"),this);
        menuBar()->addAction(nuAction);
        connect(nuAction, SIGNAL(triggered()),this, SLOT(displayNutrition()));

        fishesAction = new QAction(tr("&List Fishes"),this);
        menuBar()->addAction(fishesAction);
        connect(fishesAction, SIGNAL(triggered()),this, SLOT(displayList()));

        verAction = new QAction(tr("&Version"),this);
        menuBar()->addAction(verAction);
        connect(verAction, SIGNAL(triggered()),this, SLOT(displayVersion()));

        exitAction = new QAction(tr("&Exit"),this);
        menuBar()->addAction(exitAction);
        connect(exitAction, SIGNAL(triggered()),this, SLOT(close()));
    }

void MainWindow::displayVersion()
{
    QMessageBox::information(this,"Qt Version", qVersion());
}

 QString MainWindow::currentlySelectedItem()
 {
     QString selectedName;
     QListWidgetItem *item=NULL;

     switch (this->index)
     {
     case EBestList:
         item = this->bestList->currentItem();
         if (item)
         {
             selectedName = item->text();
         }

         break;
     case EOkList:
         item = this->okList->currentItem();
         if (item) {
             selectedName = item->text();
         }
         break;
     case EWorstList:
         item = this->worstList->currentItem();
         if (item) {
             selectedName = item->text();
         }
         break;
     }
     return selectedName;
 }

void MainWindow::displayEcoDetails()
{
    QString selectedName = this->currentlySelectedItem();

    if (selectedName.isEmpty()) {
        QMessageBox::information(this,"warning","select an item from list." );
    } else {
        this->ecoDetails->setHtml( this->fishDb->getEcoDetails(selectedName));
        this->stackedWidget->setCurrentIndex(MainWindow::EEcoPage);
    }
}

void MainWindow::displayNutrition()
{
    QString selectedName = this->currentlySelectedItem();

    if (selectedName.isEmpty()) {
        QMessageBox::information(this,"warning","select an item from list." );
    } else {
      // this->ecoDetails->setHtml( this->fishDb->getNutrition(selectedName));
        this->fishDb->getNutrition(selectedName);
        this->stackedWidget->setCurrentIndex(MainWindow::ENutritionPage);
    }
}

void MainWindow::displayList()
{
    this->stackedWidget->setCurrentIndex(MainWindow::EListPage);
}

void MainWindow::setCurrentList(int l)
{
    switch (l)
    {
    case 0:
        this->index = EBestList;
        break;
    case 1:
        this->index = EOkList;
        break;
    case 2:
        this->index = EWorstList;
        break;
    }
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
