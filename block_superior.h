#ifndef BLOCK_SUPERIOR_H
#define BLOCK_SUPERIOR_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QPainter>

class block_superior: public QObject, public QGraphicsPixmapItem
{
public:
    block_superior(QGraphicsItem* parent=nullptr);
    //void advance(int phase);

    float get_px() const{return px;}
    void set_px(float value){px=value;}

    float get_py() const{return py;}
    void set_py(float value){py=value;}

    float get_vx() const{return vx;}
    void set_vx(float value){vx=value;}

private:
    float px;
    float py;
    float vx;

};

#endif // BLOCK_SUPERIOR_H
