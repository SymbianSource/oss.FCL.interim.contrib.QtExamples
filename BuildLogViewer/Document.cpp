#include <QFile>
#include <QFileInfo>
#include <QMessageBox>

#include "Document.h"

Document::Document(QWidget *parent, QString filename) : QTreeView (parent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    QFile file(filename);
    QFileInfo fi(file);
    this->setWindowTitle(fi.baseName());

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Build Log Viewer"), tr("Cannot open log."));
        return ;
    }
    QDomDocument *log = new QDomDocument("Build Log");
    if (!log->setContent(&file)) {
        QMessageBox::warning(this, tr("Build Log Viewer"), tr("Cannot set content."));
        delete log;
        file.close();
        return ;
    }
    file.close();
    model = new DomModel(*log, this);
    this->setModel(model);
}
