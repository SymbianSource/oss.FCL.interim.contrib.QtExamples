#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "contactsengine.h"
#include "detailsgv.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // this enum is used as in index for the QStackedWidget.
    enum {EListPage = 0, // lists of contacts
          EDetailsGV}; // presents list of details for a contact based on Graphics View

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createMenus();

public slots:
    void errorOccurred(QString errMsg);
    void displayVersion();
    void displayDetails();
    void displayList();

private:
    DetailsGV *details;
    QAction *detailsAction;
    QAction *verAction;
    QAction *exitAction;

    Ui::MainWindow *ui;
    ContactsEngine *ce;
};

#endif // MAINWINDOW_H
