#include "registro.h"
#include "ui_registro.h"

registro::registro(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::registro)
{
    ui->setupUi(this);
}

registro::~registro()
{
    delete ui;
}
