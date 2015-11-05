#ifndef TANKCONTROLFORWARD_H
#define TANKCONTROLFORWARD_H

#include "tankcontrolbutton.h"

class TankControlForward : public TankControlButton
{
public:
    TankControlForward(Tank *tank);
protected:
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
};


#endif // TANKCONTROLFORWARD_H
