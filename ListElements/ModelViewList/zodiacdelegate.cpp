#include <QFile>
#include <QSvgRenderer>


#include "zodiacdelegate.h"

void ZodiacDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
           const QModelIndex &index) const
{
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);

    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
    }

    // use color assocaited with Zodiac for background.
    painter->fillRect(option.rect,index.model()->data(index,Qt::BackgroundRole).value<QBrush>());

    // draw the svg image.
    int xOffset = 10;
    int yOffset = 5;
    int height = 15;
    int width = 15;
    QRectF imgRect(option.rect.x()+xOffset,option.rect.y()+yOffset,width,height);
    QString svgFile(index.model()->data(index,Qt::DecorationRole).toString());
    QSvgRenderer renderer(svgFile);
    renderer.render(painter,imgRect);

    // now we will draw the name
    // set the pen
    painter->setPen(index.model()->data(index,Qt::TextColorRole).value<QColor>());
    // determine geometry
    int xOffsetText = 55;
    QRect rect(option.rect.x()+xOffsetText,option.rect.y(),option.rect.width(), option.rect.height());
    // write the name
    painter->drawText(rect,Qt::AlignVCenter,
                       index.model()->data(index,Qt::DisplayRole).toString());

    painter->restore();
}
