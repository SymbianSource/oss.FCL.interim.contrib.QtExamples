#ifndef DBTOOLS_H
#define DBTOOLS_H

#include <QObject>

class DBTools : QObject
{
    Q_OBJECT
public:
    explicit DBTools(QObject *parent = 0);
    ~DBTools();

public:
    void importCSV(QString fileName);
    void testDB();

signals:

public slots:

private:
    bool createDB();
    void insertContact( QString name, QString mobile, QString deskphone,
                        int xtn, QString email, QString skype,
                        QString twitter, QString title, int site,
                        int department, int floor);
    int getLastInsertRowId();
    bool createTable(QString sqlStmt);

};

#endif // DBTOOLS_H
