#include <QMenuBar>

#include <modeltest.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zodiacmodel.h"
#include "zodiacdelegate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    int heightMain = this->height();
//    int heightBar = menuBar()->height();
    ZodiacModel *zModel = new ZodiacModel(this);
//  ModelTest *m = new ModelTest(zModel, this);
    ui->listView->setModel(zModel);
    ZodiacDelegate *delegate = new ZodiacDelegate(this);
    ui->listView->setItemDelegate(delegate);
}

MainWindow::~MainWindow()
{
    delete ui;
}
