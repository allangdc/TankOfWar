#ifndef TANKCONTROLFORWARD_H
#define TANKCONTROLFORWARD_H

#include "tankcontrolbutton.h"

class TankControlForward : public TankControlButton
{
public:
    TankControlForward(Tank *tank);
protected:
    void Click(bool is_pressed);
};


#endif // TANKCONTROLFORWARD_H
