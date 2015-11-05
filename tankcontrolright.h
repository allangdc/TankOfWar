#ifndef TANKCONTROLRIGHT_H
#define TANKCONTROLRIGHT_H

#include <tankcontrolbutton.h>


class TankControlRight : public TankControlButton
{
public:
    TankControlRight(Tank *tank);
protected:
    void Click(bool is_pressed);
};

#endif // TANKCONTROLRIGHT_H
