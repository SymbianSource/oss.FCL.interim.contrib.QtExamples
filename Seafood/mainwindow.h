#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTabWidget;
class QListWidget;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createMenus();

public slots:
    void displayVersion();
    void displayPath();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QTabWidget *tabWidget;
    QListWidget *bestList;
    QListWidget *okList;
    QListWidget *worstList;

    QAction *nuAction;
    QAction *verAction;
    QAction *exitAction;
};

#endif // MAINWINDOW_H
