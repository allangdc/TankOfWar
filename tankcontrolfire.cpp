#include "tankcontrolfire.h"

#include <QDebug>

#include "protocol.h"

TankControlFire::TankControlFire(Tank *tank): TankControlButton(tank)
{
    QPixmap pxm = QPixmap(BTN_FIRE_OFF).scaled(size.toSize(),
                                           Qt::IgnoreAspectRatio,
                                           Qt::SmoothTransformation);
    this->setPixmap(pxm);
}

void TankControlFire::Click(bool is_pressed)
{
    QPixmap pxm;
    if(is_pressed) {
        pxm = QPixmap(BTN_FIRE_ON).scaled(size.toSize(),
                                               Qt::IgnoreAspectRatio,
                                               Qt::SmoothTransformation);
    } else {
        pxm = QPixmap(BTN_FIRE_OFF).scaled(size.toSize(),
                                               Qt::IgnoreAspectRatio,
                                               Qt::SmoothTransformation);
    }
    this->setPixmap(pxm);

    if(is_pressed) {
        tank->setSendValue(true);
        tank->Fire();
    }
}

