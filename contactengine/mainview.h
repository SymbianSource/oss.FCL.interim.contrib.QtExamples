#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>

#include <OLButton.h>



// Use this class with the Orange Labs FW.  Since the FW is full screen
// it handles many issues QMainWindow does for a standard Qt app.

class MainView : public QWidget
{
    Q_OBJECT
public:
    explicit MainView(QWidget *parent = 0);

signals:

public slots:
    void startApp();

    // just should all contacts.
    void showAllContacts();
    // source the list of contacts by proximity to the phone.
    void sortByGeo();
    // show all contacts at a particular event.
    void showEvents();
    // show call log
    void showLogs();

private:
    OLButton* addToolbarButton(const QString& icon, const QString& text);

private:
    int m_count;
};

#endif // MAINVIEW_H
