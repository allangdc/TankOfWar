#ifndef TANKCONTROLFIRE_H
#define TANKCONTROLFIRE_H

#include "tankcontrolbutton.h"

#define BTN_FIRE_ON     ":/image/buttons/image/fire_on.png"
#define BTN_FIRE_OFF    ":/image/buttons/image/fire_off.png"

class TankControlFire : public TankControlButton
{
public:
    TankControlFire(Tank *tank);
    void Click(bool is_pressed);
};

#endif // TANKCONTROLFIRE_H
