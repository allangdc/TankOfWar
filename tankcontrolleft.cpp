#include "tankcontrolleft.h"

TankControlLeft::TankControlLeft(Tank *tank): TankControlButton(tank)
{

}

void TankControlLeft::pressed()
{
    tank->RotateLeft(true);
}

