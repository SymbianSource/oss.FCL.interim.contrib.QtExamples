#include <QFile>
#include <QIcon>
#include <QListWidget>
#include <QMessageBox>
#include <QTableWidget>
#include <QDesktopServices>

#include "Fishes.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Fishes *f = new Fishes();

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
    setCentralWidget(tabWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenus()
    {
        nuAction = new QAction(tr("&Nutrition"),this);
        menuBar()->addAction(nuAction);
        connect(nuAction, SIGNAL(triggered()),this, SLOT(displayVersion()));

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
