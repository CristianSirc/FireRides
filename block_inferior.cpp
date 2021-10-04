#include "block_inferior.h"
#include <QBrush>
#include <QPixmap>

#include <QDebug>
block_inferior::block_inferior(QGraphicsItem  *parent): QGraphicsRectItem(parent)
{
    altura = 25+rand()%(181-25);//201
    //qDebug()<<"random :" <<altura;

    setRect(0,470,75,altura);
    QBrush brush;

    brush.setStyle(Qt::Dense1Pattern);
    brush.setColor(Qt::darkMagenta);
    setBrush(brush);
}



