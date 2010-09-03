#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    birds << "Avocet" << "Sparrow" << "Crow" << "Sea gull" << "Kookaburra";
    birdList = new QListWidget;
    setCentralWidget(birdList);
    birdList->addItems(birds);
    connect(birdList, SIGNAL(itemClicked ( QListWidgetItem * )),
               this, SLOT(displayBird(QListWidgetItem *)));
}

void MainWindow::displayBird ( QListWidgetItem * item )
{
     QMessageBox::information(this,"picked", item->text());
}

//void MainWindow::on_birdList_itemClicked(QListWidgetItem *item)
//{
//    QMessageBox::information(this, "long", item->text());
//}

MainWindow::~MainWindow()
{
    delete ui;
}
