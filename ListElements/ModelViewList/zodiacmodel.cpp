#include <QBrush>
#include <QColor>
#include <QLinearGradient>
#include <QIcon>
#include <QSvgWidget>

#include "zodiacmodel.h"
#include "zodiacsign.h"

ZodiacModel::ZodiacModel(QObject *parent) :
    QAbstractListModel(parent)
{
    // color names must match SVG standard names http://www.w3.org/TR/SVG/types.html#ColorKeywords
    this->signs.push_front( new ZodiacSign("Aries",
                                 ":/images/Aries.svg",
                                 QColor("red"),
                                 QDate(2010,3,20),
                                 QDate(2010,4,20)));

    this->signs.push_front( new ZodiacSign("Taurus",
                                 ":/images/Taurus.svg",
                                 QColor("green"),
                                 QDate(2010,4,20),
                                 QDate(2010,5,21)));

    this->signs.push_front( new ZodiacSign("Gemini",
                                 ":/images/Gemini.svg",
                                 QColor("orange"),
                                 QDate(2010,5,21),
                                 QDate(2010,6,21)));
    this->signs.push_front( new ZodiacSign("Cancer",
                                 ":/images/Cancer.svg",
                                 QColor("violet"),
                                 QDate(2010,6,21),
                                 QDate(2010,7,22)));
    this->signs.push_front( new ZodiacSign("Leo",
                                 ":/images/Leo.svg",
                                 QColor("yellow"),
                                 QDate(2010,7,22),
                                 QDate(2010,8,23)));
    this->signs.push_front( new ZodiacSign("Virgo",
                                 ":/images/Virgo.svg",
                                 QColor("white"),
                                 QDate(2010,8,23),
                                 QDate(2010,9,23)));

    this->signs.push_front( new ZodiacSign("Libra",
                                 ":/images/Libra.svg",
                                 QColor("green"),
                                 QDate(2010,9,23),
                                 QDate(2010,10,23)));

    this->signs.push_front( new ZodiacSign("Scorpio",
                                 ":/images/Scorpio.svg",
                                 QColor("maroon"),
                                 QDate(2010,10,23),
                                 QDate(2010,11,22)));
    this->signs.push_front( new ZodiacSign("Sagittarius",
                                 ":/images/Sagittarius.svg",
                                 QColor("blue"),
                                 QDate(2010,11,22),
                                 QDate(2010,12,22)));
    this->signs.push_front( new ZodiacSign("Capricorn",
                                 ":/images/Capricorn.svg",
                                 QColor("indigo"),
                                 QDate(2010,12,22),
                                 QDate(2010,1,20)));
    this->signs.push_front( new ZodiacSign("Aquarius",
                                 ":/images/Aquarius.svg",
                                 QColor("violet"),
                                 QDate(2010,1,20),
                                 QDate(2010,2,18)));
    this->signs.push_front( new ZodiacSign("Pisces",
                                 ":/images/Pisces.svg",
                                 QColor("indigo"),
                                 QDate(2010,1,20),
                                 QDate(2010,2,18)));

}

int ZodiacModel::rowCount (const QModelIndex &index) const
{
    return this->signs.count();
}

QVariant ZodiacModel::data(const QModelIndex &index, int role)const
{
    QVariant rc;

    if (!index.isValid() || index.row() >= this->signs.size()) {
         return rc;
    }
    switch (role)
    {
    case Qt::DisplayRole:
    {
        rc = QVariant(this->signs.at(index.row())->getName());
        break;
    }
    case Qt::BackgroundRole:
    {
        // a QBrush consists of a style, color, gradient and texture.
        rc = QVariant(QBrush(this->signs.at(index.row())->getColor()));

        break;
    }
    case Qt::TextColorRole:
    {
        QString name = this->signs.at(index.row())->getName();
        if (name == "Leo" || name == "Virgo")
        {
            // white text on a white or yellow background doesn't work. Let's change it.
            rc = QVariant(QColor("silver"));
        }
        break;
    }
    case Qt::DecorationRole:
    {
        rc = QVariant(this->signs.at(index.row())->getImage());
    }
    default:
        break;
    }
    return rc;
}
