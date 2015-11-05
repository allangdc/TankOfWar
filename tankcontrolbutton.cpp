#include "tankcontrolbutton.h"
#include <QTouchEvent>

TankControlButton::TankControlButton(Tank *tank) : QPushButton()
{
    this->setFocusPolicy(Qt::NoFocus);
    this->setGeometry(0,0,100,100);
    this->tank = tank;
}

