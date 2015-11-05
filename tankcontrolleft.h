#ifndef TANKCONTROLLEFT_H
#define TANKCONTROLLEFT_H

#include <tankcontrolbutton.h>

class TankControlLeft: public TankControlButton
{
public:
    TankControlLeft(Tank *tank);
protected:
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
};

#endif // TANKCONTROLLEFT_H
