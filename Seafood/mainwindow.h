#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QStackedWidget;
class QTabWidget;
class QListWidget;
class QWebView;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    enum {EListPage = 0,
          EEcoPage,
          ENutritionPage};

    void createMenus();

public slots:
    void displayVersion();
    void displayPath();
    void displayEcoDetails();
    void displayList();
    void displayNutrition();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;
    QTabWidget *tabWidget;
    QListWidget *bestList;
    QListWidget *okList;
    QListWidget *worstList;

    QWebView *ecoDetails;

    QAction *ecoAction;
    QAction *fishesAction;
    QAction *nuAction;
    QAction *verAction;
    QAction *exitAction;
};

#endif // MAINWINDOW_H
