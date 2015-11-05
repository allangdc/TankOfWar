#include "tankcontrolleft.h"
#include <QMouseEvent>

TankControlLeft::TankControlLeft(Tank *tank): TankControlButton(tank)
{
    setText("<<");
}

void TankControlLeft::mousePressEvent(QMouseEvent *e)
{
    QPushButton::mousePressEvent(e);
    if(e->button() == Qt::LeftButton) {
        //tank->RotateLeft(true);
    }
}

void TankControlLeft::mouseReleaseEvent(QMouseEvent *e)
{
    QPushButton::mouseReleaseEvent(e);
    if(e->button() == Qt::LeftButton) {
        tank->RotateLeft(false);
    }
}

