#include "zodiacsign.h"



ZodiacSign::ZodiacSign(QString aName,
           QString aUrl,
           QColor aColor,
           QDate aStart,
           QDate aEnd): name(aName),
                        image(aUrl),
                        color(aColor),
                        start(aStart),
                        end(aEnd)
{

}
