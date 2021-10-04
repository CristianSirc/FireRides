#include "instrucciones.h"
#include "ui_instrucciones.h"
#include "menu.h"
#include "ui_menu.h"


instrucciones::instrucciones(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::instrucciones)
{
    ui->setupUi(this);
}

instrucciones::~instrucciones()
{
    delete ui;
}

void instrucciones::atras()
{
    close();
    menu *activo=new menu();
    activo->show();
}


