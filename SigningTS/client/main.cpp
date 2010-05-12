#include <QtCore/QCoreApplication>
#include <QtCore/QUrl>

#include <QtDebug>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

#include "buffer.h"

QNetworkReply *addIMEI(QNetworkAccessManager *mgr)
{
    QString reqPOST = "http://localhost:8080/?key=853b128a-0c18-42f2-835f-db9f5b6f7fb9&api=1&cmd=addIMEI";
    QNetworkRequest request(QUrl(reqPOST.toUtf8()));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/xhtml+xml");

    QByteArray data;
    data.append("<SymbianSigned>");
    data.append("<IMEI>");
    data.append("<number>");
    data.append("356945030065847");
    data.append("</number>");
    data.append("<description>");
    data.append("X6 from Angela");
    data.append("</description>");
    data.append("</IMEI>");
    data.append("</SymbianSigned>");

    return mgr->post(request,data);
}

QNetworkReply *getDevCert(QNetworkAccessManager *mgr)
{
    QString reqPOST = "http://localhost:8080/?key=853b128a-0c18-42f2-835f-db9f5b6f7fb9&api=1&cmd=getDevCert&genID=456723322";
    QNetworkRequest request(QUrl(reqPOST.toUtf8()));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/xhtml+xml");

    return mgr->get(request);
}

QNetworkReply *getSubmission()
{
    QString reqGET = "http://localhost:8080/?key=853b128a-0c18-42f2-835f-db9f5b6f7fb9&api=1&cmd=getSubmission&genID=456723322";
    QNetworkRequest request(QUrl(reqGET.toUtf8()));

    return mgr->get(request);
}

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    Buffer *buf = new Buffer();
    QString reqGet = "http://localhost:8080/?key=853b128a-0c18-42f2-835f-db9f5b6f7fb9&api=1&cmd=GetUIDList" ;

    app.connect(manager, SIGNAL(finished(QNetworkReply*)),
            buf, SLOT(replyFinished(QNetworkReply*)));
    // QNetworkReply *reply = manager->get(QNetworkRequest(QUrl::fromEncoded(reqGet.toUtf8())));

    // addIMEI(manager);
    getDevCert(manager);
    // app.connect(reply, SIGNAL(finished()), SLOT(quit()));
    return app.exec();
}
