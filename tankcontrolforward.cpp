#include "tankcontrolforward.h"
#include <QMouseEvent>

TankControlForward::TankControlForward(Tank *tank): TankControlButton(tank)
{
    setText("||");
}

void TankControlForward::mousePressEvent(QMouseEvent *e)
{
    QPushButton::mousePressEvent(e);
    if(e->button() == Qt::LeftButton) {
        tank->MoveFoward(true);
    }
}

void TankControlForward::mouseReleaseEvent(QMouseEvent *e)
{
    QPushButton::mouseReleaseEvent(e);
    if(e->button() == Qt::LeftButton) {
        tank->MoveFoward(false);
    }
}

