#include "pendulo.h"
#include <QKeyEvent>
#include "block_inferior.h"
#include "block_superior.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>
#include <QString>

#include "menu.h"
#include "mundo1.h"
extern mundo1 *nivel1;

//constructor
pendulo::pendulo(double angulo)
{
    px=80;
    py=200;
    this->setPos(px,py);
    set_theta(angulo);
    velo=0;

}


pendulo::pendulo(double angulo, double pox, double poy, double l)

{
    longitud=l;
    px=pox;
    py=poy;


    this->setPos(px,py);
    set_theta(angulo);
    velo=0;

}

//Constructor con velocidad ingresada
pendulo::pendulo(double angulo,double pox,double poy,double v, double l)
{
    longitud=l;
    px=pox;
    py=poy;

    if(px>=600){px=590;}

    this->setPos(px,py);
    set_theta(angulo);
    velo=v;

}


//aceleracion angular
double pendulo::acel()
{
    double a;
    a = (-9.8*sin(to*3.1415926/180))/longitud;
    return a;
}

//velocidad angular
double pendulo::vel(double a)
{
    double v;
    v = vo + a*tiempo;
    vo = v; //se actualiza la velocidad
    return v;
}

//posicion angular
double pendulo::theta(double v, double a)
{
    double theta;
    theta = to + v*tiempo + (a*tiempo*tiempo)/2;
    to = theta;

    //qDebug()<<"angulo: "<<theto;
    return theta;

}

//SLOTS

QRectF pendulo::boundingRect() const
{
    return QRectF(px-10,py,20,longitud+20); //se configura la posicion y tamaño del pendulo (barra)
}


//para actualizar el elemento (pendulo)
void pendulo::advance(int phase)
{
    if(!phase)return;
    double a,v,p;
    a=acel();
    v=vel(a);
    p=theta(v,a);


    setTransformOriginPoint(px, py); //se cambia la posicion del eje de rotacion
    this->setRotation(p); //establece el angulo de rotación

    QList < QGraphicsItem *> colliding_items = collidingItems();
        for(int i=0,n=colliding_items.size();i<n;i++){
            if(typeid(*(colliding_items[i])) == typeid(block_inferior)){

                block_superior *exp = new block_superior();
                exp->setPixmap(QPixmap(":/explosion.png"));
                exp->setPos(px+170,py+longitud);
                scene()->addItem(exp);
                //nivel1->escena->addItem(exp);

                QMessageBox msgBox;
                msgBox.setText("COLISIÓN!!");
                msgBox.exec();
                scene()->removeItem(colliding_items[i]); //elimina los bloques de la escena
                //scene()->removeItem(this); //elimina la bola de la escena

                delete colliding_items[i]; //elimina el bloque
                msgBox.setInformativeText("Desea intentarlo de nuevo?");
                msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                msgBox.setDefaultButton(QMessageBox::Yes);
                int ret = msgBox.exec();
                switch (ret)
                {
                   case QMessageBox::Yes:

                     show();
                     delete exp;

                     //atras();
                         break;

                   case QMessageBox::No:
                    show();
                    nivel1->close();

                        break;
                    default:
                        break;
                 }

                return;
            }
        }




}

void pendulo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    QBrush pincel(Qt::black); //relleno
    QPen pen(Qt::black);            //borde
    pen.setWidthF(0.5);

    painter->setRenderHint(QPainter::Antialiasing); //para enfocar
    painter->setBrush(pincel); //se indica el Qbrush
    painter->setPen(pen); //se indica el pincel

    //Se dibujan las figuras
    painter->drawRect(px-2.5,py,5,longitud+20); //se dibuja la 'cuerda' del pendulo
    //painter->drawEllipse(px-10,py+longitud,20,20); //se dibuja la bola en la parte inferior

    QPixmap pixmap(":/symbol.png");
    painter->drawPixmap(px-10,py+longitud,20,20,pixmap);
}
