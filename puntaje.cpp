#include "puntaje.h"
#include <QFont>


puntaje::puntaje(QGraphicsItem *parent) :QGraphicsTextItem(parent)
{
    puntos=0;
    setPlainText(QString("Puntaje: ")+QString::number(puntos));
    setDefaultTextColor(Qt::white);
    setFont(QFont("times",16));

}
void puntaje::incrementa(int p)
{
    puntos+=p;
    setPlainText(QString("Puntaje: ")+QString::number(puntos));
}

int puntaje::get_puntaje()
{
    return puntos;
}


void puntaje::set_puntaje(int p)
{
    puntos=p;

}
