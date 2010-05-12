
#include "signingcommoncase.h"

SigningCommonCase::SigningCommonCase(QNetworkAccessManager &aMgr, QObject *parent) :
    QObject(parent), mgr(aMgr)
{
    testBaseURL = ::BaseURL + "?key=" + ::DefaultKey + "&api=" + ApiVersion + "&cmd=";
}

void SigningCommonCase::run()
{

}

void SigningCommonCase::uploadSIS()
{
    QString reqPOST = BaseURL + "uploadSIS";
    QNetworkRequest request(QUrl(reqPOST.toUtf8()));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"x-epoc/x-sisx-app");

    // connect this request to a method for reply.

    // here is the sis file which we will post to the server.

    //mgr.post(request);
}

TestInterface::TRESULT_STATE  SigningCommonCase::getResult()
{
   return TestInterface::INPROGESS;
}
