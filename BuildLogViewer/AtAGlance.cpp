#include <QFile>
#include <QFileInfo>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QMessageBox>

#include <QtGlobal>
#include <QRegExp>
#include <QStringList>

#include <QGridLayout>
#include <QLabel>

#include <iostream>

using namespace std;

#include "AtAGlance.h"

AtAGlance::AtAGlance(QString filename, QWidget *parent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    QFile file(filename);
    QFileInfo fi(file);
    this->setWindowTitle("Status " + fi.baseName());

    m_buildStatus = new BuildStatus();
    m_buildStatus->setTime(fi.lastModified());

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Build Log Viewer"), tr("Cannot open log."));
        return ;
    }
    m_log = new QDomDocument("Build Log");
    if (!m_log->setContent(&file)) {
        QMessageBox::warning(this, tr("Build Log Viewer"), tr("Cannot set content."));
        file.close();
        return ;
    }
    file.close();
}

AtAGlance::~AtAGlance()
{
    delete m_log;
    delete m_buildStatus;
}

// Walk Dom tree.
void AtAGlance::traveAndPopulate()
{
    this->traveAndPopulate(m_log->documentElement());
}

void AtAGlance::traveAndPopulate(QDomElement e)
{
    QString name = e.tagName();

    if (e.isNull())
    {
        return;
    }

    //  if this is an info tags, look for
    //      <info>System Definition file sf/app/organizer/package_definition.xml</info>
    if (name.compare("info",Qt::CaseInsensitive)== 0 )
    {
        // example
        // System Definition file sf/app/organizer/package_definition.xml
        QRegExp re("System*package_definition.xml");
        re.setPatternSyntax(QRegExp::Wildcard);

        if (re.exactMatch( e.text() ) )
        {
            QRegExp reToken("*package_definition.xml");
            // Which regex syntax should be used? Wildcard is ...
            reToken.setPatternSyntax(QRegExp::Wildcard);

            QStringList tokens = e.text().split(" ");
            QStringList::const_iterator constIterator;
            for (constIterator = tokens.constBegin();
                    constIterator != tokens.constEnd();
                    ++constIterator)
            {
                if (reToken.exactMatch(*constIterator))
                {
                    m_buildStatus->setName((*constIterator).toLocal8Bit().constData());
                }
            }
        }
    }

    // if this is a status tag and the exit attribute is failed, the build failed.
    if (name.compare("status",Qt::CaseInsensitive)== 0 )
    {
        QString rc = e.attribute("exit");
        if (!rc.isEmpty() && (rc.compare("failed", Qt::CaseInsensitive) == 0))
        {
            m_buildStatus->setStatus(false);
        }
    }

    // unforunately, the build log isn't valid xml.  The recipe tag often contains
    // trace output from a shell program in addition to the status tag.  Sigh.
    // So this condition looks for the status tag in the body for the recipe tag.
    // here is what the status tag should look like:
    //   <status exit='ok' attempt='1' />
    if (name.compare("recipe",Qt::CaseInsensitive)== 0 )
    {
        QRegExp re("*status exit*fail*");
        re.setPatternSyntax(QRegExp::Wildcard); 
        if (re.exactMatch(e.text()))
        {
            m_buildStatus->setStatus(false);
        }
    }

    QString text_debug;
    QDomElement e1 = e.firstChild().toElement();
    name = e1.tagName();
    text_debug = e1.text();
    while(!e1.isNull())
    {
        this->traveAndPopulate(e1);
        e1 = e1.nextSibling().toElement();
        name = e1.tagName();
        text_debug = e1.text();
    }
}

void AtAGlance::decideOnLayout()
{
    QGridLayout *layout = new QGridLayout(this);

    layout->addWidget(new QLabel("What: "), 1, 1);
    layout->addWidget(new QLabel(*m_buildStatus->name()),1,2);
    layout->addWidget(new QLabel("When: "), 2, 1);
    layout->addWidget(new QLabel(m_buildStatus->time()) ,2,2);
    layout->addWidget(new QLabel("Status: "), 3, 1);
    layout->addWidget(new QLabel(*m_buildStatus->status()),3,2);
}
