#ifndef PUNTAJE_H
#define PUNTAJE_H

#include <QGraphicsTextItem>


class puntaje: public QGraphicsTextItem
{
public:

    puntaje(QGraphicsItem * parent=0);
    void incrementa(int p);
    int get_puntaje();
    void set_puntaje(int p);
private:
    int puntos;
};

#endif // PUNTAJE_H
