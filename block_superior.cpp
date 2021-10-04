#include "block_superior.h"
#include <QBrush>

block_superior::block_superior(QGraphicsItem  *block): QGraphicsPixmapItem(block)
{
    setPixmap(QPixmap(":/2.png"));
    px=0;
    py=0;
    vx=0;

}


/*
 *     setRect(0,0,1200,100);
    QBrush brush;
    brush.setStyle(Qt::Dense1Pattern);
    brush.setColor(Qt::darkMagenta);
    setBrush(brush);
    */
