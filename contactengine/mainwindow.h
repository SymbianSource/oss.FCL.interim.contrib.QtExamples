#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "contactsengine.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createMenus();

public slots:
    void errorOccurred(QString errMsg);
    void displayVersion();


private:
    QAction *verAction;
    QAction *exitAction;
    Ui::MainWindow *ui;
    ContactsEngine *ce;
};

#endif // MAINWINDOW_H
