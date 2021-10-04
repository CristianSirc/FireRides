#include "menu.h"
#include "ui_menu.h"

#include "registro.h"
#include "ui_registro.h"
#include "instrucciones.h"
#include "ui_instrucciones.h"

//#include "mundo1.h"
//#include "instrucciones.h"
#include "mundo1.h"
#include "mundo2.h"
mundo1 *nivel1;
mundo2 *nivel2;




menu::menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
    //connect(ui->nivel1,SIGNAL(clicked()),this,SLOT(on_nivel1_clicked()));
    //connect(ui->nivel2,SIGNAL(clicked()),this,SLOT(on_nivel2_clicked()));

    //connect(ui->instrucciones,SIGNAL(clicked()),this,SLOT(instruccion()));
    //connect(ui->licencia,SIGNAL(clicked()),this,SLOT(creditos()));


}


menu::~menu()
{
    delete ui;
}

void menu::on_nivel1_clicked()
{

    nivel1=new mundo1();
    nivel1->show();
    n1=1;
    close();
}

void menu::on_nivel2_clicked()
{

    //mundo2 *nivel2 = new mundo2();
    //nivel2->show();
    nivel2=new mundo2();
    nivel2->show();
    n2=1;
    close();
}




void menu::on_jugar_clicked()
{

}



void menu::on_registro_clicked()
{
    registro *reg=new registro();
    reg->show();
    //close();

}

void menu::on_instrucciones_clicked()
{
    instrucciones *instruc=new instrucciones();
    instruc->show();
    //close();

}

