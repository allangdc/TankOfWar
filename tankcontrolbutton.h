#ifndef TANKCONTROLBUTTON_H
#define TANKCONTROLBUTTON_H

#include <QPushButton>
#include "tank.h"

class TankControlButton : public QPushButton
{
public:
    TankControlButton(Tank *tank);
protected:
    Tank *tank;
};

#endif // TANKCONTROLBUTTON_H
