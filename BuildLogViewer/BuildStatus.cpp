#include "BuildStatus.h"

BuildStatus::BuildStatus(QObject *parent)
{
    setParent(parent);
}

void BuildStatus::setTime(QDateTime w)
{
    this->m_when = w;
    this->m_status = true;
}

QString BuildStatus::Time()
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

QString BuildStatus::name()
{
    return *m_packageName;
}
