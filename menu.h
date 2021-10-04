#ifndef MENU_H
#define MENU_H

#include <QMainWindow>

namespace Ui {
class menu;
}

class menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = 0);
    ~menu();

    bool n1=0,n2=0;
    bool get_n1(){return n1;}
    bool get_n2(){return n2;}

private slots:

    void on_nivel1_clicked();
    void on_nivel2_clicked();
    void on_jugar_clicked();


    void on_registro_clicked();

    void on_instrucciones_clicked();



private:
    Ui::menu *ui;
};

#endif // MENU_H
