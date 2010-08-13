#include <QComboBox>
#include <QMenuBar>
#include <QMessageBox>

#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "contactsengine.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ce = new ContactsEngine(this);

    connect(this->ce, SIGNAL(errorOccurred(QString)),
            this,SLOT(errorOccurred(QString)));

    connect(ui->comboBox, SIGNAL( activated ( const QString &  )),
            this->ce, SLOT(setManager(const QString &) ));

    this->ce->createManager();

    ui->comboBox->addItems(this->ce->dataSources());
    ui->listView->setModel(this->ce);

    this->createMenus();
}

void MainWindow::createMenus()
    {
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

void MainWindow::errorOccurred(QString errMsg)
{
    QMessageBox::information(this,"Err Routed",errMsg);
    qDebug() << errMsg << endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}
