#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QTimer>
#include<QTransform>

#include "pendulo.h"
#include "ball.h"
#include "puntaje.h"
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow *ui;
    QGraphicsScene *escena;
    QTimer *time;

    double angulo;
    pendulo *pend1;
    ball *bola;

private slots:
    void on_GO_clicked();
    void keyPressEvent(QKeyEvent *event);

    //void on_atras_clicked();

};
#endif // MAINWINDOW_H
