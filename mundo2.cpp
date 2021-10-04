#include "mundo2.h"
#include "ui_mundo2.h"
#include<QTransform>




#include "ball.h"
#include "pendulo.h"
#include "block_superior.h"
#include "block_inferior.h"
#include "anillo.h"
#include "puntaje.h"

#include <QKeyEvent>
#include <cmath>




#include <QDebug>
#include <QImage>
#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsView>


mundo2::mundo2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mundo2)
{
    ui->setupUi(this);
    escena = new QGraphicsScene(this); //se crea la escena

    escena->setSceneRect(0,0,1200,600);
    //se agrega imagen de fondo

    escena->setBackgroundBrush(QBrush(QImage(":/monte1.JPG")));

    ui->vista->setScene(escena); //se agrega la escena a la vista

    time=new QTimer(this);
    connect(time,SIGNAL(timeout()),escena,SLOT(advance()));//conecta con el slot de pendulo
    //connect(time,SIGNAL(timeout()),this,SLOT(colision()));


    //Se agrega obstaculo superior
    for(int i=0;i<10;i++){
        block_superior *bloquesup = new block_superior();
        bloquesup->setPos(i*128,-30);
        escena->addItem(bloquesup);
    }
    //se agrega obstaculo inferior
    for(int i=0;i<16;i++){
        block_inferior *bloqueinf = new block_inferior();
        bloqueinf->set_nivel(2);
        bloqueinf->setPos(i*75,(150-bloqueinf->get_altura())); //ancho de cada bloque=75
        escena->addItem(bloqueinf);
    }

    //se agregan anillos
    for(int i=0;i<3;i++){
        anillo *ring = new anillo();
        ring->setPixmap(QPixmap(":/portal_black.png"));
        ring->setPos(i*400+200,50*pow(-1,i)+200);
        escena->addItem(ring);
    }

    //se crea el primer anillo por defecto
    pend1=new pendulo(60,50,50,200);

    //puntaje
    //puntaje *puntos = new puntaje();
    puntos=new puntaje();
    escena->addItem(puntos);
}

mundo2::~mundo2()
{
    delete ui;
}


//pasa anillos
/*void mundo2::colision(){

    //cuando la bola colisiona con los anillos
    for(int i=0;i<10;i++){
        if(bola->collidesWithItem(anillo)){
            puntos->incrementa();
            escena->removeItem(*ring); //elimina los bloques de la escena

        }
    }*/





//bool ban1=0,ban2;

void mundo2::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space){

        //balancear

        if(ban1==0){ //la primera vez que se presiona espacio
            pend1->setFlag(QGraphicsItem::ItemIsMovable);
            escena->addItem(pend1); //se agrega pendulo a la escena
            ban1=1;

        }
        else{ //despues de la primera vez: pasar de ball a pendulo

            double x=bola->get_posx()/2;
            double y=bola->get_posy();


            delete pend1;
            escena->removeItem(bola); //**************normal

            pend1=new pendulo(60,x+100,50,-1.35,-y);
            pend1->setFlag(QGraphicsItem::ItemIsMovable);
            escena->addItem(pend1); //se agrega pendulo a la escena


        }

     }

    //else if(event->isAutoRepeat())
    else if(event->key() == Qt::Key_A){

        //lanzar: pasar de pendulo a ball
        //Para hallar las posiciones
        double px=pend1->get_px();
        double py=pend1->get_py();
        double l=pend1->get_l();

        double angulo=pend1->get_theta();
        double posx=2*px-l*sin(angulo*3.14159/180); //se obtiene la posicion
        double posy=2*py+l*cos(angulo*3.14159/180);      //de la bola del pendulo

        //para hallar la velocidad
        double v = pend1->get_vel(); //se obtiene la velocidad angular del pendulo
        angulo=angulo*3.14159/180;
        v=v*-50; //se halla velocidad con v=V(angular)*R
        if(v<=-90){v=-85;} //condición para que no se dispare a muy alta velocidad
        else if(v>=90){v=85;}
        //qDebug()<<"velocidad bola: "<<v;
        angulo=angulo*-1; //Se invierte el angulo para el lanzamiento del 'proyectil'

        if(ban2==0){ //la primera vez que se presiona A
            //se asignan las ultimas posiciones del pendulo a la bola libre
            bola=new ball(posx,-posy,v,angulo);
            escena->removeItem(pend1); //se quita pendulo de la escena
            bola->setFlag(QGraphicsItem::ItemIsMovable);
            escena->addItem(bola);
            ban2=1;
        }
        else{ //despues de la primera vez
            delete bola;
            escena->removeItem(pend1); //se quita pendulo de la escena //*****normal
            bola=new ball(posx,-posy,v,angulo);
            bola->setFlag(QGraphicsItem::ItemIsMovable);
            escena->addItem(bola);
        }

    }

}




void mundo2::on_GO_clicked()
{
    ui->GO->setEnabled(false);
    //time=new QTimer(this);
    //connect(time,SIGNAL(timeout()),escena,SLOT(advance()));
    time->start(10);
}

//accion para el boton de atras - crea otro menu
/*void MainWindow::on_atras_clicked()
{
    //ui->atras->setEnabled(false);
    time->stop();
    close();
    menu *j=new menu();
    j->show();
}

//problema: al presionar espacio se cierra
*/


