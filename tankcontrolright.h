#ifndef TANKCONTROLRIGHT_H
#define TANKCONTROLRIGHT_H

#include <tankcontrolbutton.h>


class TankControlRight : public TankControlButton
{
public:
    TankControlRight(Tank *tank);
protected:
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
};

#endif // TANKCONTROLRIGHT_H
