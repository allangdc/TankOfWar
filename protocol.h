#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QObject>
#include <QByteArray>

struct CCreateTank {
    unsigned char code;
    qreal x;
    qreal y;
    qreal angle;
};

struct CTankAction {
    unsigned char code;
    unsigned char tank_id;
    unsigned char left: 1;
    unsigned char right: 1;
    unsigned char up: 1;
    unsigned char fire: 1;
};

class Protocol
{
public:
    enum msg_list {
        CREATE_TANK, TANK_ACTION
    };
    static QByteArray CreateTank(qreal x, qreal y, qreal angle);
    static QByteArray TankAction(unsigned char tank_id, bool left, bool right, bool up, bool fire);
    static unsigned char GetCode(QByteArray array);
    static CCreateTank GetCCreateTank(QByteArray array);
    static CTankAction GetCTankAction(QByteArray array);
};

#endif // PROTOCOL_H
