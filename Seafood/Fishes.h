#ifndef FISHES_H
#define FISHES_H

#include <QObject>
#include <QStringList>

class Fishes : public QObject
{
    Q_OBJECT
public:
    Fishes(QObject *parent=0);
    enum TCATEGORIES {EPresentBest=0, EPresentOK, EPresentWorst};

    const QStringList GetBest();
    const QStringList GetOK();
    const QStringList GetWorst();

    QString getEcoDetails(QString name);

private:
    void populate(TCATEGORIES cat);
    QStringList bestFish;
    QStringList okFish;
    QStringList worstFish;
};

#endif // FISHES_H
