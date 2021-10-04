#ifndef ANILLO_H
#define ANILLO_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPainter>

class anillo:  public QObject, public QGraphicsPixmapItem
{
public:
    anillo(QGraphicsItem *ani=0);
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

#endif // ANILLO_H
