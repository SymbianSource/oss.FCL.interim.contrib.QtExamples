#include <QMenuBar>
#include <QMessageBox>
#include <QResizeEvent>
#include <QtGlobal>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zodiacmodel.h"
#include "zodiacdelegate.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create widgets.
    listView = new QListView;
    listView->setFrameStyle(QFrame::Panel | QFrame::Raised);
    listView->setLineWidth(4);
    exitButton = new QPushButton(this);
    exitButton->setText("Exit");

    // define the model
    ZodiacModel *zModel = new ZodiacModel(this);
    listView->setModel(zModel);
    ZodiacDelegate *delegate = new ZodiacDelegate(this);
    listView->setItemDelegate(delegate);

    // create landscape layout
    layoutLandscape = new QHBoxLayout(this);
    layoutLandscape->addWidget(listView);
    layoutLandscape->addWidget(exitButton);

    //create portrait layout
    layoutPortrait = new QVBoxLayout(this);
    layoutPortrait->addWidget(listView);
    layoutPortrait->addWidget(exitButton);

    portLandLayout = new PLLayout();
    portLandLayout->setPLayout(layoutPortrait);
    portLandLayout->setLLayout(layoutLandscape);

    centralWidget = new QWidget();
    centralWidget->setLayout(portLandLayout);
    this->setCentralWidget(centralWidget);

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    portLandLayout->resizeEvent(e);
    // Call base class impl
    QWidget::resizeEvent(e);
}
