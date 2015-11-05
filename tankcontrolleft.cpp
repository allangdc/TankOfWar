#include "tankcontrolleft.h"
#include <QPixmap>

TankControlLeft::TankControlLeft(Tank *tank): TankControlButton(tank)
{
    this->setRotation(90);
}

void TankControlLeft::Click(bool is_pressed)
{
    TankControlButton::Click(is_pressed);
    tank->RotateLeft(is_pressed);
}
