#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSignalMapper>

#include <QtGui/QMainWindow>
#include <QtGui/QWorkspace>

#include "Document.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void notYetImplemented();
    void openLog();
    void enableActions();
    void closeEvent(QCloseEvent *event);

private:
    Document *activeDocument();
    void createActions();
    void updateWindowList();


    Ui::MainWindow *ui;
    QWorkspace *workspace;
    QSignalMapper *mapper;
};

#endif // MAINWINDOW_H
