#include <QFile>
#include <QFileInfo>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QMessageBox>

#include <QtGlobal>
#include <QRegExp>

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
        QRegExp re("^System Definition file .*package_definition.*$");
        re.setPatternSyntax(QRegExp::Wildcard);

        string blah = e.text().toStdString();

        if (re.exactMatch( e.text() ) )
        {
            std::cout << "info: " << e.text().toStdString()<< std::endl;
        }
    }

    // if this is a status tag and the exit attribute is failed, the build failed.
    if (name.compare("status",Qt::CaseInsensitive)== 0 )
    {
        m_buildStatus->setStatus(false);
    }

    QString text_debug;
    QDomElement e1 = e.firstChild().toElement();
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
    layout->addWidget(new QLabel("When: "), 2, 1);
    layout->addWidget(new QLabel("Status: "), 3, 1);
}
