#ifndef SIGNINGCOMMONCASE_H
#define SIGNINGCOMMONCASE_H

#include <QObject>
#include <QtCore/QUrl>

#include <QtDebug>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>



#include "test.h"

/**
  This is the original puesdo-code for this test.
 This walks through signing.  Express and Certified signing are very similar.

 sign sis file with publisher ID

 type is one of express or certified.
submissionID,type = uploadSIS(sisfile)

createSigningRequest(submissionID, type, description)

done = false
do {
    status = getSubmissionStatus(submissionID)
    switch (status)
    {
        case SIGNED:
            done = true
            break;
        case SCAN_FAILED:
            done = true
            break;
        case TEST_FAILED:
            done = true
            break;
        case TESTING_IN_PROGRESS:
        case AUDIT_IN_PROGRESS:
            // This take awhile. Probably don't want to poll. IDEs may want to check for outstanding
            // submissions when IDE is started. see enumerateSubmissions
            break;
        default:
            sleep(2000);
    }

} while (!done)

if (status == SIGNED) getSubmission(submissionID)
  */

class SigningCommonCase : public QObject, public TestInterface
{
    Q_OBJECT
public:
    explicit SigningCommonCase(QNetworkAccessManager &mgr, QObject *parent = 0);

    void run();
    TRESULT_STATE getResult();

signals:

public slots:


private:
    void uploadSIS();
    QString testBaseURL;
    QNetworkAccessManager &mgr;
};

#endif // SIGNINGCOMMONCASE_H
