#ifndef ATAGLANCE_H
#define ATAGLANCE_H

#include <QDomElement>
#include <QWidget>

#include "BuildStatus.h"

/*
  * This class presents the status for a given build.  It gets the
  * appropriate data from the model.
  */

class AtAGlance : public QWidget
{
    Q_OBJECT

public:
    AtAGlance(QString filename, QWidget *parent = 0 );
    ~AtAGlance();

    void traveAndPopulate();
    void decideOnLayout();
private:
    void traveAndPopulate(QDomElement e);

private:
    QDomDocument *m_log;
    BuildStatus *m_buildStatus;
};

#endif // ATAGLANCE_H
