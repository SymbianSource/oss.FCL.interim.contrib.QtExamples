#include <QNetworkReply>
#include <QtDebug>
#include "buffer.h"

void Buffer::replyFinished(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    qDebug() << "result: " << data << endl;
    reply->deleteLater();
}

Buffer::Buffer(QObject *parent) :
    QObject(parent)
{
}
