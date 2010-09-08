#include <QMenuBar>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zodiacmodel.h"
#include "zodiacdelegate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ZodiacModel *zModel = new ZodiacModel(this);
    ui->listView->setModel(zModel);
    ZodiacDelegate *delegate = new ZodiacDelegate(this);
    ui->listView->setItemDelegate(delegate);
}

MainWindow::~MainWindow()
{
    delete ui;
}
