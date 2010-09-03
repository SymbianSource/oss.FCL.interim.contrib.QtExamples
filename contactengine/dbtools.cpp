#include <QtCore/QCoreApplication>
#include <QFile>

#include <QDebug>
#include <QStringList>

#include "database.h"
#include "dbtools.h"


void DBTools::importCSV(QString fileName)
{
    QFile file(fileName);
    QString line;

    if (file.open(QFile::ReadOnly)) {
        qDebug() << "importCSV file open OK" << endl;
        char buf[1024];

        while(!file.atEnd())
        {
            file.readLine(buf, sizeof(buf));
            QString string(buf);

            QStringList stringList = string.split(",");

            QString strName;
            QString strMobile;
            QString strDeskphone;
            QString strXtn;
            QString strEmail;
            QString strFloor;
            QString strSkype;
            QString strTwitter;
            QString strTitle;
            QString strSite;
            QString strDepartment;

            if (stringList.count() > 0)
                strName = stringList[0];

            if (stringList.count() > 1)
                strMobile = stringList[1];

            if (stringList.count() > 2)
                strDeskphone = stringList[2];

            if (stringList.count() > 3)
                strXtn = stringList[3];

            if (stringList.count() > 4)
                strEmail = stringList[4];

            if (stringList.count() > 5)
                strSkype = stringList[5];

            if (stringList.count() > 6)
                strTwitter = stringList[6];

            if (stringList.count() > 7)
                strTitle = stringList[7];

            if (stringList.count() > 8)
                strSite = stringList[8];

            if (stringList.count() > 9)
                strDepartment = stringList[9];

            if (stringList.count() > 10)
                strFloor =stringList[10];

            qDebug() << strName << strTitle << endl;
      }
    }
}

DBTools::DBTools(QObject *parent)
{
    QObject();
}

DBTools::~DBTools()
{

}
