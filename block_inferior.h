#ifndef BLOCK_INFERIOR_H
#define BLOCK_INFERIOR_H


#include <QGraphicsRectItem>
#include "string.h"
//#include <QPainter>

class block_inferior: public QGraphicsRectItem
{

    double altura;
    int nivel;
public:
    block_inferior(QGraphicsItem* parent=nullptr);

    double get_altura(){return altura;}
    double set_nivel(int n){nivel = n;}


};


#endif // BLOCK_INFERIOR_H
