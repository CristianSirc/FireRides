#ifndef BALL_H
#define BALL_H

#include <QGraphicsItem>
#include <math.h>
#include <QPainter>
#include <QTimer>

#include "puntaje.h"

#include <QKeyEvent>

class ball : public QObject, public QGraphicsItem
{
    Q_OBJECT
private:
    const double t=0.05; //delta de tiempo
    const double g=9.8; //gravedad
    double posx;
    double posy;
    double velocidad; //magnitud de la velocidad
    double angulo;
    double velx;
    double vely;
    int r; //radio de la bola

    //puntaje *puntos;

    //double ax; //aceleracion en x
    //double ay; //aceleracion en y
    //double k=0.01; //resistencia del aire
    //double e=0.8; //coeficiente de restitucion

public:

    ball(); //constructor por defecto
    ball(double x,double y,double v,double a);//constructor

    void calcularPosicion();
    void calcularVelocidad();
    //getters
    double get_posx() const{return posx;}
    double get_posy() const{return posy;}
    double get_velx(){return velx;}
    double get_vely(){return vely;}

    //setters
    void set_posx(double pox){posx=pox;}
    void set_posy(double poy){posy=poy;}
    void set_vel(double v){velocidad=v;}
    void set_ang(double ang){angulo=ang;}

    void set_velx(double vx){velx=vx;}
    void set_vely(double vy){vely=vy;}


    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);


public slots:
    void moveBall();


};

#endif // BALL_H
