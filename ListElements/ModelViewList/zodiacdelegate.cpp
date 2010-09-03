#include <QFile>
#include <QSvgRenderer>


#include "zodiacdelegate.h"

void ZodiacDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
           const QModelIndex &index) const
{
    painter->save();
    painter->setPen(Qt::red);
    painter->setBrush(Qt::yellow);
    painter->setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);

    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, option.palette.highlight());
    }

    // draw the svg image.
    int xOffset = 10;
    int yOffset = 5;
    int height = 15;
    int width = 15;
    QRectF imgRect(option.rect.x()+xOffset,option.rect.y()+yOffset,width,height);
    QString svgFile(index.model()->data(index,Qt::DecorationRole).toString());
    QSvgRenderer renderer(svgFile);
    renderer.render(painter,imgRect);

    // write the name
    int xOffsetText = 55;
    QRect rect(option.rect.x()+xOffsetText,option.rect.y(),option.rect.width(), option.rect.height());
    painter->drawText(rect,Qt::AlignVCenter,
                       index.model()->data(index,Qt::DisplayRole).toString());

    // just for debugging
    QPoint point(option.rect.x()+xOffsetText,option.rect.y());
    painter->drawLine(point+QPoint(-5,0),point+QPoint(5,0));
    painter->drawLine(point+QPoint(0,-5),point+QPoint(0,5));

    painter->restore();
}
