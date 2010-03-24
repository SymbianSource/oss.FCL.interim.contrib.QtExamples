#include <QFileDialog>
#include <QMessageBox>

#include "AtAGlance.h"
#include "Document.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // MDI from Chap 4, page 105 Foundamentals of Qt Development
    workspace = new QWorkspace();
    setCentralWidget(workspace);
    connect(workspace, SIGNAL(windowActivated(QWidget*)),
            this, SLOT(enableActions()));
    mapper = new QSignalMapper(this);
    connect(mapper, SIGNAL(mapped(QWidget*)),
            workspace, SLOT(setActiveWindow(QWidget*)));

    this->createActions();
    this->enableActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::notYetImplemented()
{
    QMessageBox::information(this, tr("Build Log Viewer"), tr("Not Yet Implemented."));
}

 void MainWindow::openLog()
 {
    QString filename = QFileDialog::getOpenFileName(
             this, tr("Open Log"), QDir::currentPath(),
             tr("Build log *.xml;;All files (*.*)"));
    Document *doc = new Document(this, filename);
    workspace->addWindow(doc);

    doc->show();
 }

 void MainWindow::showStatus()
 {
    QString filename = QFileDialog::getOpenFileName(
        this, tr("Open Log"), QDir::currentPath(),
        tr("Build log *.xml;;All files (*.*)"));
    AtAGlance *aag = new AtAGlance(filename, this);
    workspace->addWindow(aag);
    aag->traveAndPopulate();
    // obsolete using BuildResults.ui now.
    // aag->decideOnLayout();
    aag->show();
 }

 void MainWindow::createActions()
 {
    // file menu - mark as NYI
    //connect(ui->actionOpen, SIGNAL(triggered()),
    //      this, SLOT(openLog()));
    connect(ui->actionOpen, SIGNAL(triggered()),
            this, SLOT(showStatus()));
    connect(ui->actionClose, SIGNAL(triggered()),
            workspace, SLOT(closeActiveWindow()));

    // find menu - mark as NYI
    connect(ui->actionFind, SIGNAL(triggered()),
            this, SLOT(notYetImplemented()));
    connect(ui->actionTags , SIGNAL(triggered()),
            this, SLOT(notYetImplemented()));

    // window menu - mark as NYI
    connect(ui->actionTile , SIGNAL(triggered()),
        this, SLOT(notYetImplemented()));
    connect(ui->actionCascade , SIGNAL(triggered()),
        this, SLOT(notYetImplemented()));
    connect(ui->actionNext_Window , SIGNAL(triggered()),
        this, SLOT(notYetImplemented()));
    connect(ui->actionPrevious_Window , SIGNAL(triggered()),
        this, SLOT(notYetImplemented()));

    ui->actionSeparator->setSeparator(true);
 }

 void MainWindow::enableActions()
 {
     bool hasDocuments = (activeDocument() != 0) ;
     // file
     ui->actionOpen->setEnabled(true);
     ui->actionClose->setEnabled(hasDocuments);
     ui->actionQuit->setEnabled(true);
     // find
     ui->actionFind->setEnabled(hasDocuments);
     ui->actionTags->setEnabled(hasDocuments);
     // window
     ui->actionCascade->setEnabled(hasDocuments);
     ui->actionTile->setEnabled(hasDocuments);
     ui->actionNext_Window->setEnabled(hasDocuments);
     ui->actionPrevious_Window->setEnabled(hasDocuments);
     ui->actionSeparator->setEnabled(hasDocuments);
 }

 void MainWindow::updateWindowList()
 {
     ui->menuWindow->clear();

     ui->menuWindow->addAction(ui->actionTile);
     ui->menuWindow->addAction(ui->actionCascade);
     ui->menuWindow->addSeparator();
     ui->menuWindow->addAction(ui->actionNext_Window);
     ui->menuWindow->addAction(ui->actionPrevious_Window);
     // If there are no open logs, we will disable this one.
     ui->menuWindow->addAction(ui->actionSeparator);

     int i=1;
     foreach(QWidget *w, workspace->windowList())
     {
          QString text;
          if ( i< 10) {
              text = QString("&%1 %2").arg(i++).arg(w->windowTitle());
          } else {
              text = w->windowTitle();
          }

          QAction *action = ui->menuWindow->addAction(text);
          action->setCheckable(true);
          action->setChecked(w == activeDocument());
          connect(action,SIGNAL(triggered()),
                  mapper, SLOT(map()));
          mapper->setMapping(action, w);
      }
 }

void MainWindow::closeEvent(QCloseEvent *event)
{
    workspace->closeAllWindows();
}

Document * MainWindow::activeDocument()
{
    return qobject_cast<Document*>(workspace->activeWindow());
}
