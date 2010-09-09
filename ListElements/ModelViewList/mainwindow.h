#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFrame>
#include <QListView>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QWidget>
#include "PLLayout.h"
#include "zodiacsign.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void resizeEvent(QResizeEvent *e);

private:
    Ui::MainWindow *ui;

    QHBoxLayout *layoutLandscape;
    QWidget *centralWidget;
    QVBoxLayout *layoutPortrait;

    QPushButton *exitButton;
    QListView *listView;
    PLLayout *portLandLayout;


};

#endif // MAINWINDOW_H
