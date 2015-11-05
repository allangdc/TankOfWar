#include "tankcontrolforward.h"
#include <QPixmap>

TankControlForward::TankControlForward(Tank *tank): TankControlButton(tank)
{
    this->setRotation(180);
}

void TankControlForward::Click(bool is_pressed)
{
    TankControlButton::Click(is_pressed);
    tank->MoveFoward(is_pressed);
}

