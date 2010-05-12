#ifndef BUFFER_H
#define BUFFER_H

#include <QObject>

class QNetworkReply;

class Buffer : public QObject
{
Q_OBJECT
public:
    explicit Buffer(QObject *parent = 0);

signals:

public slots:
    void replyFinished(QNetworkReply *reply);

};

#endif // BUFFER_H
