#ifndef PENDULO_H
#define PENDULO_H

#include <QGraphicsItem>
#include <cmath>
#include <QPainter>
#include <QString>
class pendulo: public QObject,  public QGraphicsItem
{
    Q_OBJECT
private:

    double longitud=200;
    double tiempo=0.5;

    double px; //posiciones del eje de rotacion del pendulo
    double py;

    double acel(); //aceleracion angular
    double vel(double a);   //velocidad angular
    double theta(double v, double a); //posicion angular

    double theto; //pos angular inicial
    double velo; //vel angular inicial
    double &to = theto; //referencias a pos-angular0 y vel-angular0
    double &vo = velo;

public:
    pendulo(double angulo); //constructor
    pendulo(double angulo,double pox,double poy, double l);
    pendulo(double angulo,double pox,double poy,double v, double l);


    void set_theta(double ang){theto=ang;}
    //getters
    double get_px(){return px;}
    double get_py(){return py;}
    double get_theta(){return theto;}
    double get_vel(){return velo;}
    double get_l(){return longitud;}

    //setters
    void set_px(double pox){px=pox;}
    void set_py(double poy){py=poy;}
    void set_l(double l){l=longitud;}



public slots:
    void advance(int phase);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // PENDULO_H
