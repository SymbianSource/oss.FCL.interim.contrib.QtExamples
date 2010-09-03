#ifndef ZODIACSIGN_H
#define ZODIACSIGN_H

#include <QColor>
#include <QDate>
#include <QString>


class ZodiacSign : public QObject
{
    Q_OBJECT
public:
    explicit ZodiacSign(QString name,
               QString sign,
               QColor color,
               QDate start,
               QDate end);
    QString getName() { return name;}
    QString getImage() { return image; }
    QColor getColor() {return color; }
    QDate getStart() {return start; }
    QDate getEnd() {return end; }

private:
      QString name;
      QString image;
      QColor color;
      QDate start;
      QDate end;
};

#endif // ZODIACSIGN_H
