#include <QComboBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "contactsengine.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ce = new ContactsEngine(this);
  //  this->ce->enumerateMgrs();
    this->ce->setManager(QString("memory"));

    connect(ui->comboBox, SIGNAL( activated ( const QString &  )),
            this->ce, SLOT(setManager(const QString &) ));

    ui->comboBox->addItems(this->ce->dataSources());
    this->ce->populateAddresses();
 //   this->ce->enumerateMgrs();
  //  this->ce->dumpContactMgr();
    ui->listView->setModel(this->ce);
}



MainWindow::~MainWindow()
{
    delete ui;
}
