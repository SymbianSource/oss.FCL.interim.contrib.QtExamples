#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QStringList>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void displayBird( QListWidgetItem * item );
    // void on_birdList_itemClicked(QListWidgetItem * );
private:
    QStringList birds;
    QListWidget *birdList;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
