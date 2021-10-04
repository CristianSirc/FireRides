#include "ball.h"
#include <QPixmap>
#include <QTimer>
#include <QObject>

#include "block_inferior.h"
#include "block_superior.h"
#include "anillo.h"

#include <QGraphicsScene>
#include <QList>


#include "mundo1.h"
extern mundo1 *nivel1;
#include "mundo2.h"
extern mundo2 *nivel2;

#include <QMessageBox>
#include <QString>
#include <QDebug>

//#include "menu.h"
//extern menu *menu;


//constructor por defecto
ball::ball(){
    posx=0;
    posy=0;
    angulo=0;
    velocidad=0;
    velx=0;
    vely=0;
    r=10;
}
//constructor
ball::ball(double x,double y,double v,double a){
    posx=x+r;
    posy=y;
    velocidad=v;
    angulo=a;
    velx=0;
    vely=0;
    r=10;

    setPos(posx,-posy);
    //Conexion

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(moveBall()));
    timer->start(10);
}


void ball::calcularPosicion()
{
   calcularVelocidad();
   //Calculo de posiciones
   posx+=velx*t;
   posy+=vely*t-(0.5*g*t*t);
   //posx+=velx*t + ((ax*(t*t))/2);
   //posy+=vely*t-(0.5*ay*t*t);

    setPos(posx,-posy); //se actualiza la posicion
}

void ball::calcularVelocidad()
{

    //calculo de velocidades
    velx=velocidad*cos(angulo);
    vely=velocidad*sin(angulo)-g*t;

    //velx=velx + ax*t;
    //vely=vely + ay*t;

    //ax = -((k*(velocidad*velocidad)*(r*r))/10)*cos(angulo); //masa=10
    //ay = (-((k*(velocidad*velocidad)*(r*r))/10)*sin(angulo))-g;

    //************  CHOQUE CON LOS BORDES + restitucion
    if(posx+r >=1200 || posx-r<0) //780
        velx=-velx*0.95;

    if(posy-r<=-600)
        vely=-vely*0.89;
    if(posy+r>=-100)
        vely=-vely;

    velocidad= sqrt(velx*velx+vely*vely);
    angulo=atan2(vely,velx);

}




int flag=0;
void ball::moveBall()
{
    calcularPosicion();
    //int p=nivel1->puntos->get_puntaje();
    //nivel1->puntos->set_puntaje(p+posx/1000);

    //en la lista se guardan todos los bloques inferiores
    //cuando colisiona la bola con los obstaculos inferiores
    QList < QGraphicsItem *> colliding_items = collidingItems();
        for(int i=0,n=colliding_items.size();i<n;i++){
            if(typeid(*(colliding_items[i])) == typeid(block_inferior)){

                block_superior *exp = new block_superior();
                exp->setPixmap(QPixmap(":/explosion.png"));
                exp->setPos(posx-50,-posy-50);
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
                     this->set_posx(100);
                     this->set_posy(200);
                     this->set_velx(5);
                     this->set_vely(5);
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

        //cuando la bola colisiona con los anillos

       QList < QGraphicsItem *> quiebra_anillos = collidingItems();
            for(int i=0,n=quiebra_anillos.size();i<n;i++){
                if(typeid(*(quiebra_anillos[i])) == typeid(anillo)){


                    block_superior *quiebra = new block_superior();
                    quiebra->setPixmap(QPixmap(":/quiebra1.png"));
                    quiebra->setPos(posx-50,-posy-50);
                    scene()->addItem(quiebra);

                    flag=flag+1;
                    qDebug()<<flag<<endl;

                    nivel1->puntos->incrementa(posx/10);
                    //nivel2->puntos->incrementa();
                    if(flag==3){
                        QMessageBox msgBox;
                        msgBox.setText("GANASTE!!");
                        msgBox.exec();

                        msgBox.setInformativeText("Desea intentarlo de nuevo?");
                        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                        msgBox.setDefaultButton(QMessageBox::Yes);
                        int ret = msgBox.exec();
                        switch (ret)
                        {
                           case QMessageBox::Yes:

                             show();
                             //atras();
                                 break;

                           case QMessageBox::No:
                            show();
                            nivel1->close();
                                break;
                            default:
                                break;
                         }
                    }


                     /*if(menu->get_n1()==1 && menu->get_n2()==0){
                           nivel1->puntos->incrementa();
                     }
                     else if(menu->get_n1()==0 && menu->get_n2()==1){
                           nivel2->puntos->incrementa();
                     }*/


                    scene()->removeItem(quiebra_anillos[i]); //elimina los bloques de la escena


                    delete quiebra_anillos[i]; //elimina el bloque
                    return;
                }
            }


}

//se limita posicion graficamente
QRectF ball::boundingRect() const
{
    return QRectF(-r,-r,2*r,2*r);
}

void ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap(":/symbol.png");
    painter->setRenderHint(QPainter::Antialiasing);
    //painter->setBrush(Qt::darkMagenta);
    //painter->drawEllipse(boundingRect());
    painter->drawPixmap(-r,-r,2*r,2*r,pixmap);
}
