#ifndef REGISTRO_H
#define REGISTRO_H

#include <QMainWindow>

namespace Ui {
class registro;
}

class registro : public QMainWindow
{
    Q_OBJECT

public:
    explicit registro(QWidget *parent = nullptr);
    ~registro();

private:
    Ui::registro *ui;
};

#endif // REGISTRO_H
