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
    enum TNUTRITION {ECalories = 0, ETotalFat, ETotalProtein,
                     EOmega3, ECholesterol, ESodium, EMaxNutrients };

    const QStringList getBest();
    const QStringList getOK();
    const QStringList getWorst();

    QString getEcoDetails(QString name);
    QMap<TNUTRITION, QString> getNutrition(QString name);

private:
    void populate(TCATEGORIES cat);
    QStringList bestFish;
    QStringList okFish;
    QStringList worstFish;
};

#endif // FISHES_H
