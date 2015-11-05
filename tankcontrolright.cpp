#include "tankcontrolright.h"
#include <QPixmap>

TankControlRight::TankControlRight(Tank *tank): TankControlButton(tank)
{
    this->setRotation(-90);
}

void TankControlRight::Click(bool is_pressed)
{
    TankControlButton::Click(is_pressed);
    tank->RotateRight(is_pressed);
}


