#include "mundo1.h"
#include "ui_mundo1.h"

#include "menu.h"
//menu *menu;

#include<QTransform>

#include "ball.h"
#include "pendulo.h"
#include "block_superior.h"
#include "block_inferior.h"
#include "anillo.h"
#include "puntaje.h"

#include <QKeyEvent>
#include <cmath>

#include "menu.h"


#include <QDebug>
#include <QImage>
#include <QBrush>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsView>


mundo1::mundo1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mundo1)
{
    ui->setupUi(this);
    escena = new QGraphicsScene(this); //se crea la escena

    escena->setSceneRect(0,0,1200,600);
    //se agrega imagen de fondo

    escena->setBackgroundBrush(QBrush(QImage(":/paisaje33.JPG")));

    ui->vista->setScene(escena); //se agrega la escena a la vista

    time=new QTimer(this);
    connect(time,SIGNAL(timeout()),escena,SLOT(advance()));//conecta con el slot de pendulo


    timer_control=new QTimer;
    control = new QSerialPort(this);
    connect(timer_control,SIGNAL(timeout()),this,SLOT(arduino()));


    //Se agrega obstaculo superior
    for(int i=0;i<10;i++){
        block_superior *bloquesup = new block_superior();
        bloquesup->setPos(i*128,-30);
        escena->addItem(bloquesup);
    }
    //se agrega obstaculo inferior
    for(int i=0;i<16;i++){
        block_inferior *bloqueinf = new block_inferior();
        bloqueinf->setPos(i*75,150-bloqueinf->get_altura()); //ancho de cada bloque=75
        escena->addItem(bloqueinf);
    }

    //se agregan anillos
    for(int i=0;i<3;i++){
        anillo *ring = new anillo();
        ring->setPos(i*400+200,50*pow(-1,i)+200);
        escena->addItem(ring);
    }

    //se crea el primer anillo por defecto
    pend1=new pendulo(60,50,50,200);

    //puntaje
    puntos = new puntaje();
    escena->addItem(puntos);

    time->start(10);

}

mundo1::~mundo1()
{
    delete ui;
}




void mundo1::keyPressEvent(QKeyEvent *event)
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

            pend1=new pendulo(60,x+100,50,-0.9,-y);
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

void mundo1::arduino(){

    char data;
    int l=0;
    bool flag=true;

    if(control->waitForReadyRead(100)){
        //Data was returned
        l = control->read(&data,1);
        switch (data) {

        //balancear
        case 'B':
        {
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

                pend1=new pendulo(60,x+100,50,-0.9,-y);
                pend1->setFlag(QGraphicsItem::ItemIsMovable);
                escena->addItem(pend1); //se agrega pendulo a la escena


            }

        }break;
        case 'A':
        {
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

        }break;



        default:
            break;
        }


        qDebug()<<"Response: "<<data;
        flag=false;

    }else{
        //No data
//        qDebug()<<"Time out";
   }
}








void mundo1::on_atras_clicked()
{
    time->stop();
    close();
    menu *j=new menu();
    j->show();

}


void mundo1::on_pushButton_clicked()
{
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText("conexion arduino");
    QPushButton *saveButton = msgBox.addButton(tr("Conectar"), QMessageBox::AcceptRole);
    QPushButton *discardButton = msgBox.addButton(tr("Desconectar"), QMessageBox::RejectRole);

    msgBox.exec();
    if (msgBox.clickedButton() == saveButton) {
        //iniciar la conexion
        control->setPortName("COM7");
        timer_control->start(1000);
        if(control->open(QIODevice::ReadWrite)){
            //Ahora el puerto seria está abierto
            if(!control->setBaudRate(QSerialPort::Baud9600)) //Configurar la tasa de baudios
                qDebug()<<control->errorString();

            if(!control->setDataBits(QSerialPort::Data8))
                qDebug()<<control->errorString();

            if(!control->setParity(QSerialPort::NoParity))
                qDebug()<<control->errorString();

            if(!control->setStopBits(QSerialPort::OneStop))
                qDebug()<<control->errorString();

            if(!control->setFlowControl(QSerialPort::NoFlowControl))
                qDebug()<<control->errorString();
                timer_control->start(20);
        }
        else{
            qDebug()<<"Serial COM7 not opened. Error: "<<control->errorString();
        }
    } else if (msgBox.clickedButton() == discardButton) {
        timer_control->stop();
        control->close();
        msgBox.close();
    }
    delete saveButton;
    delete discardButton;

}
