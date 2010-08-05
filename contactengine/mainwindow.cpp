#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "contactsengine.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ce = new ContactsEngine(this);

    ui->comboBox->addItems(this->ce->dataSources());

}

void MainWindow::backendSelected(QString txt)
{
    // based on this string create a contact manager.
    this->ce->setManager(txt);
}

MainWindow::~MainWindow()
{
    delete ui;
}
