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
    Fishes *f = new Fishes();

    this->stackedWidget = new QStackedWidget;

    this->tabWidget = new QTabWidget;
    // QIcon icon = new QIcon(":/database/icons/weather-sunny.svg");
    // this->tabWidget->setTabIcon(1, icon);

    this->bestList = new QListWidget;
    this->bestList->addItems(f->GetBest());
    this->tabWidget->addTab(this->bestList, "best");

    this->okList = new QListWidget;
    this->okList->addItems(f->GetOK());
    this->tabWidget->addTab(this->okList, "ok");

    this->worstList = new QListWidget;
    this->worstList->addItems(f->GetWorst());
    this->tabWidget->addTab(this->worstList, "worst");

    this->stackedWidget->addWidget(tabWidget); // associated with EListPage

    this->ecoDetails = new QWebView;
    this->ecoDetails->setHtml("<html><title>Eco Details</title><ul><li>not yet implemented</li></ul></html>");

    this->stackedWidget->addWidget(this->ecoDetails); // associated with EEcoPage

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
//    QMessageBox::information(this,"Qt Version", qVersion());
     QMessageBox::information(this,"selected item", "NYI");
}

void MainWindow::displayNutrition()
{
    this->stackedWidget->setCurrentIndex(MainWindow::ENutritionPage);
}

void MainWindow::displayEcoDetails()
{
    this->stackedWidget->setCurrentIndex(MainWindow::EEcoPage);
}

void MainWindow::displayList()
{
    this->stackedWidget->setCurrentIndex(MainWindow::EListPage);
}

void MainWindow::displayPath()
{
    QString dbFile = QDesktopServices::storageLocation(QDesktopServices::DataLocation)
                     + '/'  // Qt Universal file separator
                     + "seafood.db";
    QFile f(dbFile);
    if (f.exists()) {
        QMessageBox::information(this,"db not found ", dbFile);
    } else {
        QMessageBox::information(this,"found db @ ", dbFile);
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
