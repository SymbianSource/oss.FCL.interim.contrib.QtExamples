#ifndef BUILDSTATUS_H
#define BUILDSTATUS_H

#include <QObject>
#include <QDateTime>

class BuildStatus : public QObject
{
    Q_OBJECT

public:
    BuildStatus(QObject *parent = 0);

public slots:
    void setName(QString n);
    void setStatus (bool n );
    void setTime(QDateTime w);

signals:
    void textEmitted(const QString &);

public:
    const QString *name();
    const QString *status();
    QString time();

private:
    // What was the name of the package?
    QString *m_packageName;
    // At this time, the symbain build log doesn't have a timestamp in it.
    // So, we will use the timestamp on the file.
    QDateTime m_when;
    // Did the build succeed?
    bool m_status;
    QString *m_PresentStatus;
};

#endif // BUILDSTATUS_H
