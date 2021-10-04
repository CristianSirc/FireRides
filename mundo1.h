#ifndef MUNDO1_H
#define MUNDO1_H

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

#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class mundo1;
}

class mundo1 : public QMainWindow
{
    Q_OBJECT

private:
    QTimer *timer_control;
    QSerialPort *control;
    QMessageBox msgBox;


public:
    explicit mundo1(QWidget *parent = nullptr);
    ~mundo1();
    Ui::mundo1 *ui;
    QGraphicsScene *escena;
    QTimer *time;

    double angulo;
    puntaje *puntos;
    pendulo *pend1;
    ball *bola;

    bool ban1=0,ban2=0;


private slots:

    void keyPressEvent(QKeyEvent *event);
    void on_atras_clicked();
    void on_pushButton_clicked();

    void arduino();
};

#endif // MUNDO1_H
