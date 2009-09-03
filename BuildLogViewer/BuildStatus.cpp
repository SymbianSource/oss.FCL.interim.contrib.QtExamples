#include "BuildStatus.h"

BuildStatus::BuildStatus(QObject *parent)
{
    setParent(parent);
    this->m_packageName = new QString("<unknown>");
    this->m_PresentStatus = new QString("Pass");
    this->m_status = true;
}

void BuildStatus::setTime(QDateTime w)
{
    this->m_when = w;
}

QString BuildStatus::time()
{
    return this->m_when.toString();
}

void BuildStatus::setName(QString n)
{
    if (m_packageName)
    {
        delete m_packageName;
        m_packageName = NULL;
    }
    m_packageName = new QString(n);
}

const QString *BuildStatus::name()
{
    return m_packageName;
}

void BuildStatus::setStatus (bool n )
{
    m_status = n ;
    if (!m_status)
    {
        this->m_PresentStatus = new QString("Failed");
    }
}


const QString  *BuildStatus::status()
{
    return this->m_PresentStatus;
}
