#ifndef TANKCONTROLLEFT_H
#define TANKCONTROLLEFT_H

#include <tankcontrolbutton.h>

class TankControlLeft: public TankControlButton
{
public:
    TankControlLeft(Tank *tank);
protected:
    void pressed();
};

#endif // TANKCONTROLLEFT_H
