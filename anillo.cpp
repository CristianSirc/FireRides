#include "anillo.h"
#include <QBrush>
#include <QPixmap>

anillo::anillo(QGraphicsItem* ani):QGraphicsPixmapItem(ani)
{

    setPixmap(QPixmap(":/portal.png"));
    px=400;
    py=200;
    vx=0;
    //setPos(px,py);
}

/*void anillo::advance(int phase){
    setPos(px,py);
}
*/


/*anillo::anillo(QGraphicsItem *parent): QGraphicsEllipseItem(parent)
{
    setRect(400,300,50,150);
    QBrush brush;
    brush.setStyle(Qt::Dense7Pattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);

}*/
