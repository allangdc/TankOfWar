#include "tankcontrolright.h"
#include <QMouseEvent>

TankControlRight::TankControlRight(Tank *tank): TankControlButton(tank)
{
    setText(">>");
}

void TankControlRight::mousePressEvent(QMouseEvent *e)
{
    QPushButton::mousePressEvent(e);
    if(e->button() == Qt::LeftButton) {
        tank->RotateRight(true);
    }
}

void TankControlRight::mouseReleaseEvent(QMouseEvent *e)
{
    QPushButton::mouseReleaseEvent(e);
    if(e->button() == Qt::LeftButton) {
        tank->RotateRight(false);
    }
}

