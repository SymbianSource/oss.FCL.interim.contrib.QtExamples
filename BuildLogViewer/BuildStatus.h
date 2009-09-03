#ifndef BUILDSTATUS_H
#define BUILDSTATUS_H

#include <QObject>
#include <QDateTime>

class BuildStatus : public QObject
{
public:
    BuildStatus(QObject *parent = 0);

    void setName(QString n);
    QString name();

    void setTime(QDateTime w);
    QString Time();

    void setStatus (bool n ) { m_status = n ; } ;



    // What was the name of the package?
    QString *m_packageName;
    // At this time, the symbain build log doesn't have a timestamp in it.
    // So, we will use the timestamp on the file.
    QDateTime m_when;
    // Did the build succeed?
    bool m_status;
};

#endif // BUILDSTATUS_H
