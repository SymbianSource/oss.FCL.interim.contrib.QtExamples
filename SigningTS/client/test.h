#ifndef TEST_H
#define TEST_H

#include <qstring.h>

// Each test will be a subclass of this abstract class.
// A test has a sequence of steps. Each step is composed of
// a request and reply.

const QString BaseURL = "http://localhost:8080/";
const QString DefaultKey = "853b128a-0c18-42f2-835f-db9f5b6f7fb9";
const int ApiVersion = 1;

class TestInterface
{

public:
    virtual void  run () = 0 ; // run the test.

    enum TRESULT_STATE { PASS=0, FAIL, INPROGESS} ;
    virtual TRESULT_STATE getResult() = 0;


    enum TAPI_SIGNING_STATE { SUBMITTED=0, SCANNED, FAILED_SCAN, SIGNED,
                              AUDIT_IN_PROGRESS, FAILED_TESTING,
                              TESTING_IN_PROGRESS};
};

#endif // TEST_H
