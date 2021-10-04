#ifndef MUNDO2_H
#define MUNDO2_H


#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QTimer>
#include<QTransform>

#include "pendulo.h"
#include "ball.h"
#include "puntaje.h"
#include "anillo.h"
#include <QKeyEvent>

namespace Ui {
class mundo2;
}

class mundo2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit mundo2(QWidget *parent = nullptr);
    ~mundo2();

    Ui::mundo2 *ui;
    QGraphicsScene *escena;
    QTimer *time;

    double angulo;
    puntaje *puntos;
    pendulo *pend1;
    ball *bola;

    bool ban1=0,ban2=0;



private slots:
    void on_GO_clicked();
    void keyPressEvent(QKeyEvent *event);
    //void colision();

    //void on_atras_clicked();
};



#endif // MUNDO2_H
