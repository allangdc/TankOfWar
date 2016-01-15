#include "protocol.h"

QByteArray Protocol::CreateTank(qreal x, qreal y, qreal angle)
{
    struct CCreateTank c;
    char *ch = (char *) &c;
    c.code = (unsigned char) CREATE_TANK;
    c.angle = angle;
    c.x = x;
    c.y = y;
    QByteArray array(ch, sizeof(CCreateTank));
    return array;
}

QByteArray Protocol::TankAction(unsigned char tank_id, bool left, bool right, bool up, bool fire)
{
    struct CTankAction c;
    char *ch = (char *) &c;
    c.code = (unsigned char) TANK_ACTION;
    c.tank_id = tank_id;
    c.left = left?1:0;
    c.right = right?1:0;
    c.up = up?1:0;
    c.fire = fire?1:0;
    QByteArray array(ch, sizeof(CCreateTank));
    return array;
}

unsigned char Protocol::GetCode(QByteArray array)
{
    unsigned char code = (unsigned char) array.at(0);
    return code;
}

CCreateTank Protocol::GetCCreateTank(QByteArray array)
{
    CCreateTank *c = (CCreateTank *) array.data();
    return *c;
}

CTankAction Protocol::GetCTankAction(QByteArray array)
{
    CTankAction *c = (CTankAction *) array.data();
    return *c;
}


